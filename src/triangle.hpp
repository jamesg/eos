#ifndef EOS_TRIANGLE_HPP
#define EOS_TRIANGLE_HPP

#include "coloured.hpp"
#include "material.hpp"
#include "primitive.hpp"

namespace eos
{
    class triangle : public virtual primitive, public coloured, public material
    {
    public:
        triangle();
        triangle(Eigen::Matrix<double, 3, 3>);
        triangle(Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d);

        using material::reflectivity;

        void set_points(Eigen::Matrix3d);

        bool intersects(const ray& light_ray) const override;
        Eigen::Vector3d
            closest_intersection(const ray& light_ray) const override;
        Eigen::Vector3d normal(Eigen::Vector3d) const override;
        void transform(transform_type) override;
    private:
        Eigen::Matrix<double, 3, 3> m_points;
    };
}

#endif

