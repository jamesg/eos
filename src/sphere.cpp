#include "sphere.hpp"

#include <stdexcept>

namespace
{
    template<typename Scalar>
    Scalar square(Scalar x)
    {
        return x * x;
    }
}

bool eos::sphere::intersects(const ray& light_ray) const
{
    return (
            square(
                light_ray.direction.dot(light_ray.start - this->centre)
                ) -
            square((light_ray.start - this->centre).norm()) +
            square(this->radius)
            ) >= 0.0;
}

Eigen::Vector3f eos::sphere::closest_intersection(const ray& light_ray) const
{
    if(!this->intersects(light_ray))
        throw std::runtime_error("no intersection");
    float d =
        -(light_ray.direction.normalized().dot(light_ray.start - this->centre))
        -sqrt(
            square(
                light_ray.direction.normalized().dot(
                    light_ray.start - this->centre
                    )
                ) -
            square((light_ray.start - this->centre).norm()) +
            square(this->radius)
            );
    return light_ray.start + d*light_ray.direction.normalized();
}

