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
    m_radius(1)
{
}

void eos::sphere::set_radius(double radius)
{
    m_radius = radius;
}

bool eos::sphere::intersects(const ray& light_ray) const
{
    double det = intersection_determinant(light_ray);
    //return (det > 0.0);
    if(det < 0.0)
        return false;
    // Check that the intersection is on the outside of the sphere.
    double d1 = (
            -(light_ray.direction().dot(light_ray.origin() - centre())) +
            sqrt(det)
            );
    double d2 = (
            -(light_ray.direction().dot(light_ray.origin() - centre())) -
            sqrt(det)
            );
    // Both points of intersection are ahead of the ray origin.
    return (d1 >= 0.0 && d2 >= 0.0);
}

Eigen::Vector3d eos::sphere::closest_intersection(const ray& light_ray) const
{
    if(!this->intersects(light_ray))
        throw std::runtime_error("no intersection");
    float d =
        -(light_ray.direction().dot(light_ray.origin() - centre()))
        -sqrt(intersection_determinant(light_ray));
    return light_ray.origin() + d*light_ray.direction();
}

Eigen::Vector3d eos::sphere::normal(Eigen::Vector3d loc) const
{
    return (loc - centre()).normalized();
}

double eos::sphere::intersection_determinant(const ray& light_ray) const
{
    return
        square(light_ray.direction().dot(light_ray.origin() - centre())) -
        square((light_ray.origin() - centre()).norm()) +
        square(m_radius);
}

void eos::sphere::transform(transform_type)
{
}

