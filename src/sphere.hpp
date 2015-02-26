#ifndef EOS_SPHERE_HPP
#define EOS_SPHERE_HPP

#include "primitive.hpp"
#include "raytracer.hpp"

namespace eos
{
    class sphere : public primitive
    {
    public:
        sphere();

        void set_centre(Eigen::Vector3d);
        void set_radius(double r);

        pixel colour() const;
        void set_colour(const pixel&);

        bool intersects(const ray& light_ray) const override;
        Eigen::Vector3d
            closest_intersection(const ray& light_ray) const override;
        Eigen::Vector3d normal(Eigen::Vector3d) const override;
    private:
        Eigen::Vector3d m_centre;
        double m_radius;
        pixel m_colour;
        double m_reflectivity, m_specvalue, m_specpower;
    };
}

#endif

