#ifndef EOS_SPHERE_HPP
#define EOS_SPHERE_HPP

#include "coloured.hpp"
#include "primitive.hpp"
#include "raytracer.hpp"

namespace eos
{
    class sphere : public virtual primitive, public coloured
    {
    public:
        sphere();

        using coloured::colour;

        void set_centre(Eigen::Vector3d);
        void set_radius(double r);

        bool intersects(const ray& light_ray) const override;
        Eigen::Vector3d
            closest_intersection(const ray& light_ray) const override;
        Eigen::Vector3d normal(Eigen::Vector3d) const override;
    private:
        Eigen::Vector3d m_centre;
        double m_radius;
    };
}

#endif

