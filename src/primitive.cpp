#include "primitive.hpp"

eos::pixel eos::primitive::colour() const
{
    return pixel(1, 1, 1);
}

eos::pixel eos::primitive::diffuse(const lamp& l, const ray& view_ray) const
{
    // Intensity of diffuse light = direction of light dot normal times
    // colour times incident light intensity.
    // Id = (L . N) C Il
    if(!intersects(view_ray))
        return eos::pixel(0, 0, 0);
    auto x = closest_intersection(view_ray);
    auto light_direction = (x - l.centre).normalized();
    double brightness = (-light_direction).dot(normal(x)) * l.brightness;
    if(brightness < 0)
        brightness = 0;
    if(brightness > 1)
        brightness = 1;
    return brightness*colour();
}

