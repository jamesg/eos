#ifndef EOS_RAYTRACER_HPP
#define EOS_RAYTRACER_HPP

#include <vector>

#include <Eigen/Core>

namespace eos
{
    typedef Eigen::Vector3d pixel;

    struct lamp
    {
        Eigen::Vector3d centre;
        float brightness;

        lamp() :
            brightness(1.0)
        {
        }
    };

}

#endif

