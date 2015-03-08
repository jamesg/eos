#include "soft_lamp.hpp"

#include <algorithm>
#include <cstdlib>

#include <Eigen/Geometry>

#include "sampling.hpp"

eos::soft_lamp::soft_lamp() :
    m_softness(4.0)
{
}

std::vector<Eigen::Vector3d> eos::soft_lamp::ray_origin() const
{
    const double RANDOMNESS = 1.0;
    std::vector<Eigen::Vector3d> samples(sample8(m_softness, RANDOMNESS));
    std::vector<Eigen::Vector3d> origins;
    Eigen::Translation<double, 3> translation(centre());
    std::transform(
            samples.begin(),
            samples.end(),
            std::back_inserter(origins),
            [translation](const Eigen::Vector3d& origin) {
                return translation * origin;
            }
            );
    return origins;
}

void eos::soft_lamp::set_softness(double softness)
{
    m_softness = softness;
}

