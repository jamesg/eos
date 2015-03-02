#include "lamp.hpp"

eos::lamp::lamp() :
    m_brightness(1.0),
    m_centre(0, 0, 0)
{
}

double eos::lamp::brightness() const
{
    return m_brightness;
}

void eos::lamp::set_brightness(double brightness)
{
    m_brightness = brightness;
}

Eigen::Vector3d eos::lamp::centre() const
{
    return m_centre;
}

void eos::lamp::set_centre(Eigen::Vector3d centre)
{
    m_centre = centre;
}

int eos::lamp::ray_count() const
{
    return 1;
}

