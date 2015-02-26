#ifndef EOS_TRIANGLE_HPP
#define EOS_TRIANGLE_HPP

#include "primitive.hpp"

namespace eos
{
    class triangle : public primitive
    {
    public:
        triangle(Eigen::Matrix<double, 3, 3>);
        triangle(Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d);

        bool intersects(const ray& light_ray) const override;
        Eigen::Vector3d
            closest_intersection(const ray& light_ray) const override;
        Eigen::Vector3d normal(Eigen::Vector3d) const override;
    private:
        Eigen::Matrix<double, 3, 3> m_points;
    };
}

#endif

