#include "main.hpp"

#include <fstream>
#include <iostream>

#include "commandline/commandline.hpp"

#include "image.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

int eos::main(int argc, const char **argv)
{
    std::string outfile;
    bool show_help = false;
    std::vector<commandline::option> cmd_options{
        commandline::parameter("outfile", outfile, "Output filename"),
        commandline::flag("help", show_help, "Show this help message")
    };
    commandline::parse(argc, argv, cmd_options);

    if(show_help)
    {
        commandline::print(argc, argv, cmd_options);
        return 0;
    }

    if(outfile == "")
    {
        std::cerr << "error: output file must be specified" << std::endl;
        commandline::print(argc, argv, cmd_options);
        return 1;
    }

    scene s;
    {
        std::unique_ptr<sphere> o(new sphere);
        o->set_centre({0, 200, 0});
        o->set_radius(190);
        o->set_colour({0, 1, 0});
        s.add(std::move(o));
    }

    s.add(
        std::unique_ptr<triangle>(
            new triangle(
                Eigen::Vector3d(150, 0, 250),
                Eigen::Vector3d(150, 0, 0),
                Eigen::Vector3d(350, 0, 0)
                )
            )
        );

    s.add(
        std::unique_ptr<triangle>(
            new triangle(
                Eigen::Vector3d(0, 0, 250),
                Eigen::Vector3d(0, 0, 0),
                Eigen::Vector3d(150, 0, 0)
                )
            )
        );

    s.add(
        std::unique_ptr<triangle>(
            new triangle(
                Eigen::Vector3d(-150, 0, -250),
                Eigen::Vector3d(-150, 0, 0),
                Eigen::Vector3d(-350, 0, 0)
                )
            )
        );

    // Strong light from above-left illuminates the scene.
    {
        lamp l;
        l.centre = {-200, -200, -200};
        l.brightness = 0.8;
        s.add(l);
    }
    // Weak light from the camera illuminates everything the camera can see.
    {
        lamp l;
        l.centre = {0, -200, 0};
        l.brightness = 0.3;
        s.add(l);
    }

    image output(800, 600);
    for(int ix = 0; ix < output.width(); ++ix)
    {
        for(int iy = 0; iy < output.height(); ++iy)
        {
            try
            {
                if(ix == 265 && iy == 162)
                    throw std::runtime_error("break");
            }
            catch(const std::exception&)
            {
            }
            Eigen::Vector3d start =
                {
                    -(float(ix) - output.width()/2),
                    -1000,
                    -(float(iy) - output.height()/2)
                };
            ray view_ray(
                start,
                Eigen::Vector3d{0, -500, 0} - start
            );
            output.set({ix, iy}, s.compute_colour(view_ray, 1));
        }
    }

    std::ofstream os(outfile);
    os << output;
    return 0;
}

int main(int argc, const char **argv)
{
    return eos::main(argc, argv);
}

