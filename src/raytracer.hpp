#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP

#include <Eigen/Core>

namespace raytracer
{
    typedef Eigen::Matrix<unsigned char, 3, 1> pixel;

    struct sphere {
        Eigen::Vector3f centre;
        float radius;
        pixel colour;
        float reflectivity, specvalue, specpower;

        sphere() :
            radius(0.0),
            reflectivity(1.0),
            specvalue(0.0),
            specpower(0.0)
        {
        }
    };

    struct lamp {
        Eigen::Vector3f centre;
        float brightness;

        lamp() :
            brightness(1.0)
        {
        }
    };
}

#endif

