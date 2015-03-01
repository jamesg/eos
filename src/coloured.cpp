#include "coloured.hpp"

eos::coloured::coloured() :
    m_colour({0.0, 0.0, 0.0})
{
}

eos::coloured::coloured(const pixel colour) :
    m_colour(colour)
{
}

eos::pixel eos::coloured::colour() const
{
    return m_colour;
}

void eos::coloured::set_colour(const pixel colour)
{
    m_colour = colour;
}

