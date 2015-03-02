#include "soft_lamp.hpp"

eos::soft_lamp::soft_lamp() :
    m_normal(0, 1, 0)
{
}

Eigen::Vector3d eos::soft_lamp::ray_origin() const
{
    return centre();
}

int eos::soft_lamp::ray_count() const
{
    return 16;
}

Eigen::Vector3d eos::soft_lamp::normal() const
{
    return m_normal;
}

void eos::soft_lamp::set_normal(Eigen::Vector3d normal)
{
    m_normal = normal;
}

