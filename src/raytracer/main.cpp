#include "main.hpp"

#include <fstream>
#include <iostream>

#include "commandline/commandline.hpp"
#include "styx/list.hpp"

#include "image.hpp"
#include "lamp.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "scene_file.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

int eos::main(int argc, const char **argv)
{
    std::string infile, outfile;
    bool show_help = false;
    std::vector<commandline::option> cmd_options{
        commandline::parameter("infile", infile, "Input filename"),
        commandline::parameter("outfile", outfile, "Output filename"),
        commandline::flag("help", show_help, "Show this help message")
    };
    commandline::parse(argc, argv, cmd_options);

    if(show_help)
    {
        commandline::print(argc, argv, cmd_options);
        return 0;
    }

    if(infile == "")
    {
        std::cerr << "error: input file must be specified" << std::endl;
        commandline::print(argc, argv, cmd_options);
        return 1;
    }
    if(outfile == "")
    {
        std::cerr << "error: output file must be specified" << std::endl;
        commandline::print(argc, argv, cmd_options);
        return 1;
    }

    scene s = scene_file::from_file(infile).get_scene();

    image output(800, 600);
    for(int ix = 0; ix < output.width(); ++ix)
    {
        for(int iy = 0; iy < output.height(); ++iy)
        {
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

