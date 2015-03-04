#include "soft_lamp.hpp"

#include <cstdlib>

#include <Eigen/Geometry>

eos::soft_lamp::soft_lamp() :
    m_normal(0, 1, 0),
    m_softness(4.0)
{
}

std::vector<Eigen::Vector3d> eos::soft_lamp::ray_origin() const
{
    std::vector<Eigen::Vector3d> origins;
    Eigen::AngleAxisd rotation(
        std::acos(Eigen::Vector3d::UnitY().dot(m_normal)/m_normal.norm()),
        Eigen::Vector3d::UnitY().cross(m_normal)
        );
    for(int i = 0; i < 4; ++i)
    {
        origins.push_back(
            rotation *
            Eigen::Translation<double, 3>(centre()) *
            Eigen::Vector3d{
                m_softness * (i/2 + ((double)std::rand()/RAND_MAX) - 1.0),
                0,
                m_softness * (i%2 + ((double)std::rand()/RAND_MAX) - 1.0)
            }
            );
    }
    return origins;
}

Eigen::Vector3d eos::soft_lamp::normal() const
{
    return m_normal;
}

void eos::soft_lamp::set_normal(Eigen::Vector3d normal)
{
    m_normal = normal;
}

void eos::soft_lamp::set_softness(double softness)
{
    m_softness = softness;
}

