#include "sphere.hpp"

#include <stdexcept>

#include "ray.hpp"

namespace
{
    template<typename Scalar>
    Scalar square(Scalar x)
    {
        return x * x;
    }
}

eos::sphere::sphere() :
    m_radius(1),
    m_colour({255, 255, 255}),
    m_reflectivity(1),
    m_specvalue(0),
    m_specpower(0)
{
}

void eos::sphere::set_centre(Eigen::Vector3d centre)
{
    m_centre = centre;
}

void eos::sphere::set_radius(double radius)
{
    m_radius = radius;
}

eos::pixel eos::sphere::colour() const
{
    return m_colour;
}

void eos::sphere::set_colour(const pixel& colour)
{
    m_colour = colour;
}

bool eos::sphere::intersects(const ray& light_ray) const
{
    return (
            square(
                light_ray.direction().dot(light_ray.origin() - m_centre)
                ) -
            square((light_ray.origin() - m_centre).norm()) +
            square(m_radius)
            ) >= 0;
}

Eigen::Vector3d eos::sphere::closest_intersection(const ray& light_ray) const
{
    if(!this->intersects(light_ray))
        throw std::runtime_error("no intersection");
    float d =
        -(light_ray.direction().dot(light_ray.origin() - m_centre))
        -sqrt(
            square(
                light_ray.direction().dot(
                    light_ray.origin() - m_centre
                    )
                ) -
            square((light_ray.origin() - m_centre).norm()) +
            square(m_radius)
            );
    return light_ray.origin() + d*light_ray.direction();
}

Eigen::Vector3d eos::sphere::normal(Eigen::Vector3d loc) const
{
    return (loc - m_centre).normalized();
}

