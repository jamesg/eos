#include "material.hpp"

eos::material::material() :
    m_reflectivity(0.0),
    m_specvalue(0.0),
    m_specpower(0.0)
{
}

eos::material::material(
        double reflectivity,
        double specvalue,
        double specpower
        ) :
    m_reflectivity(reflectivity),
    m_specvalue(specvalue),
    m_specpower(specpower)
{
}

double eos::material::reflectivity() const
{
    return m_reflectivity;
}

double eos::material::specvalue() const
{
    return m_specvalue;
}

double eos::material::specpower() const
{
    return m_specpower;
}

void eos::material::set_reflectivity(double reflectivity)
{
    m_reflectivity = reflectivity;
}

void eos::material::set_specvalue(double specvalue)
{
    m_specvalue = specvalue;
}

void eos::material::set_specpower(double specpower)
{
    m_specpower = specpower;
}

void eos::material::set_material_attributes(
        double reflectivity,
        double specpower,
        double specvalue
        )
{
    m_reflectivity = reflectivity;
    m_specvalue = specvalue;
    m_specpower = specpower;
}

