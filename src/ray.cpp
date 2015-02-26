#include "ray.hpp"

eos::ray::ray(const Eigen::Vector3d& s, const Eigen::Vector3d& d) :
    m_start(s),
    m_direction(d.normalized())
{
}

Eigen::Vector3d eos::ray::origin() const
{
    return m_start;
}

Eigen::Vector3d eos::ray::direction() const
{
    return m_direction;
}

void eos::ray::set_origin(Eigen::Vector3d origin)
{
    m_start = origin;
}

void eos::ray::set_direction(Eigen::Vector3d direction)
{
    m_direction = direction;
    m_direction.normalize();
}

