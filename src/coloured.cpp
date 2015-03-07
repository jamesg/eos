#include "coloured.hpp"

eos::coloured::coloured() :
    m_colour(0.0, 0.0, 0.0, 0.0)
{
}

eos::coloured::coloured(const colour::rgba colour) :
    m_colour(colour)
{
}

eos::colour::rgba eos::coloured::colour() const
{
    return m_colour;
}

void eos::coloured::set_colour(const colour::rgba colour)
{
    m_colour = colour;
}

