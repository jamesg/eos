#include "primitive.hpp"

#include "lamp.hpp"

eos::colour::rgba eos::primitive::colour() const
{
    return colour::rgba(1, 1, 1, 1);
}

double eos::primitive::reflectivity() const
{
    return 0.0;
}

eos::colour::rgba eos::primitive::diffuse(const lamp& l, const ray& view_ray) const
{
    // Intensity of diffuse light = direction of light dot normal times
    // colour times incident light intensity.
    // Id = (L . N) C Il
    if(!intersects(view_ray))
        return colour::rgba();
    auto x = closest_intersection(view_ray);
    auto light_direction = (x - l.centre()).normalized();
    double brightness = (-light_direction).dot(normal(x)) * l.brightness();
    if(brightness < 0)
        brightness = 0;
    if(brightness > 1)
        brightness = 1;

    colour::rgba out;
    out << brightness*colour().block<3, 1>(0, 0), 1.0;
    return out;
}

