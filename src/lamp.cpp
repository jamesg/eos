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

