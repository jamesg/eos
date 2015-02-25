#ifndef EOS_SPHERE_HPP
#define EOS_SPHERE_HPP

#include "raytracer.hpp"

namespace eos
{
    struct sphere
    {
        Eigen::Vector3f centre;
        float radius;
        pixel colour;
        float reflectivity, specvalue, specpower;

        sphere() :
            radius(1.0),
            reflectivity(1.0),
            specvalue(0.0),
            specpower(0.0)
        {
        }

        bool intersects(const ray& light_ray) const;
        Eigen::Vector3f closest_intersection(const ray& light_ray) const;
    };
}

#endif

