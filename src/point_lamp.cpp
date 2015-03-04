#include "point_lamp.hpp"

std::vector<Eigen::Vector3d> eos::point_lamp::ray_origin() const
{
    return std::vector<Eigen::Vector3d>{centre()};
}

