#ifndef EOS_RAYTRACER_HPP
#define EOS_RAYTRACER_HPP

#include <vector>

#include <Eigen/Core>

namespace eos
{
    typedef Eigen::Matrix<unsigned char, 3, 1> pixel;

    struct lamp
    {
        Eigen::Vector3f centre;
        float brightness;

        lamp() :
            brightness(1.0)
        {
        }
    };

    struct ray
    {
        Eigen::Vector3f start, direction;
    };
}

#endif

