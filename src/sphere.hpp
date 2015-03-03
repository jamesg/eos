#ifndef EOS_SPHERE_HPP
#define EOS_SPHERE_HPP

#include "attributes.hpp"
#include "coloured.hpp"
#include "material.hpp"
#include "pixel.hpp"
#include "primitive.hpp"

namespace eos
{
    class sphere :
        public virtual primitive,
        public coloured,
        public has_centre,
        public material
    {
    public:
        sphere();

        using coloured::colour;
        using material::reflectivity;

        void set_radius(double r);

        bool intersects(const ray& light_ray) const override;
        Eigen::Vector3d
            closest_intersection(const ray& light_ray) const override;
        Eigen::Vector3d normal(Eigen::Vector3d) const override;
        void transform(transform_type) override;
    private:
        double intersection_determinant(const ray&) const;
        double m_radius;
    };
}

#endif

