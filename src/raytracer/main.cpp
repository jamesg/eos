#include "main.hpp"

#include <iostream>

#include "image.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

int eos::main(int argc, char **argv)
{
    scene s;
    {
        std::unique_ptr<sphere> o(new sphere);
        o->set_centre({0, 100, 0});
        o->set_radius(250);
        o->set_colour({1, 1, 1});
        //s.add(std::move(o));
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
                Eigen::Vector3d(0, 100, 250),
                Eigen::Vector3d(0, 100, 0),
                Eigen::Vector3d(150, 100, 0)
                )
            )
        );

    s.add(
        std::unique_ptr<triangle>(
            new triangle(
                Eigen::Vector3d(-150, 200, -250),
                Eigen::Vector3d(-150, 200, 0),
                Eigen::Vector3d(-350, 200, 0)
                )
            )
        );

    {
        lamp l;
        l.centre = {-200, -200, -200};
        l.brightness = 0.8;
        s.add(l);
    }
    //{
        //lamp l;
        //l.centre = {0, -200, 0};
        //l.brightness = 0.2;
        //s.add(l);
    //}
    // TODO: use quarternion
    ray camera({0, -1, 0}, {0, 1, 0});

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

    std::cout << output;
    return 0;
}

int main(int argc, char **argv)
{
    return eos::main(argc, argv);
}

