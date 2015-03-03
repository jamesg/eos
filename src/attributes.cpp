#include "attributes.hpp"

eos::attributes::~attributes()
{
}

eos::has_centre::has_centre() :
    m_centre(0, 0, 0)
{
}

eos::has_centre::has_centre(Eigen::Vector3d centre) :
    m_centre(centre)
{
}

Eigen::Vector3d eos::has_centre::centre() const
{
    return m_centre;
}

void eos::has_centre::set_centre(Eigen::Vector3d centre)
{
    m_centre = centre;
}

