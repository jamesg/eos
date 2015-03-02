#include "point_lamp.hpp"

Eigen::Vector3d eos::point_lamp::ray_origin() const
{
    return centre();
}

