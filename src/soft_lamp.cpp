#include "soft_lamp.hpp"

#include <cstdlib>

#include <Eigen/Geometry>

eos::soft_lamp::soft_lamp() :
    m_softness(4.0)
{
}

std::vector<Eigen::Vector3d> eos::soft_lamp::ray_origin() const
{
    std::vector<Eigen::Vector3d> origins;
    for(int i = 0; i < 8; ++i)
    {
        origins.push_back(
            Eigen::Translation<double, 3>(centre()) *
            Eigen::Vector3d{
                m_softness * (i/4 + ((double)std::rand()/RAND_MAX) - 1.0),
                m_softness * ((i%4)/2 + ((double)std::rand()/RAND_MAX) - 1.0),
                m_softness * (i%2 + ((double)std::rand()/RAND_MAX) - 1.0)
            }
            );
    }
    return origins;
}

void eos::soft_lamp::set_softness(double softness)
{
    m_softness = softness;
}

