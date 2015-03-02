#include "scene.hpp"

#include <algorithm>
#include <iostream>

#include "lamp.hpp"
#include "ray.hpp"

eos::pixel eos::scene::background_colour() const
{
    return pixel({1, 1, 1});
}

eos::pixel eos::scene::compute_colour(const ray& view_ray, int recursions) const
{
    auto distance = [this, view_ray](const primitive *s) {
        return (s->closest_intersection(view_ray) - view_ray.origin()).norm();
    };
    auto cmp = [distance](const primitive *s1, const primitive *s2) {
        return distance(s1) < distance(s2);
    };
    auto not_in_line = [distance, view_ray](const primitive *s) {
        return !s->intersects(view_ray);
    };

    // Set up a view onto all shapes in the scene.
    std::vector<const primitive*> primitives;
    std::transform(
            m_primitives.begin(),
            m_primitives.end(),
            std::back_inserter(primitives),
            [](const std::unique_ptr<primitive>& p) {
                return p.get();
            }
            );
    // Remove shapes that are not on the line of the view ray.
    primitives.erase(
            std::remove_if(primitives.begin(), primitives.end(), not_in_line),
            primitives.end()
            );

    if(primitives.size() == 0)
        return background_colour();

    // Sort primitives on the view ray by distance from the camera.
    std::sort(primitives.begin(), primitives.end(), cmp);

    pixel out({0, 0, 0});

    const primitive *closest = primitives.at(0);
    auto intersection = closest->closest_intersection(view_ray);

    // Check if 'shape' intersects 'light_ray' between the light ray origin and
    // 'closest'.  In other words, check if primitive 'shape' casts a shadow on
    // 'closest'.
    auto in_ray = [&closest](
            const std::unique_ptr<primitive>& shape,
            ray light_ray
            )
    {
        if(!shape->intersects(light_ray) || !closest->intersects(light_ray))
            return false;
        double lamp_closest = (
                closest->closest_intersection(light_ray) -
                light_ray.origin()
                ).norm();
        double lamp_shape = (
                shape->closest_intersection(light_ray) -
                light_ray.origin()
                ).norm();
        return (lamp_closest > lamp_shape);
    };

    for(const std::unique_ptr<lamp>& current_lamp_ptr : m_lamps)
    {
        const lamp& current_lamp = *current_lamp_ptr;
        const int ray_count = current_lamp.ray_count();
        eos::pixel ray_colour(0, 0, 0);
        for(int i = 0; i < ray_count; ++i)
        {
            // lamp -> intersection
            ray light_ray(
                    current_lamp.centre(),
                    intersection - current_lamp.centre()
                    );

            // Find objects along the line from the lamp to the object.  If
            // there are objects along this line, there will be a shadow on the
            // object.
            if(
                std::find_if(
                    m_primitives.begin(),
                    m_primitives.end(),
                    std::bind(in_ray, std::placeholders::_1, light_ray)
                    ) == m_primitives.end()
              )
                ray_colour += closest->diffuse(current_lamp, view_ray);
        }
        ray_colour /= ray_count;
        out += ray_colour;
    }

    return out;
}

void eos::scene::add(std::unique_ptr<lamp>&& l)
{
    m_lamps.push_back(std::move(l));
}

void eos::scene::add(std::unique_ptr<primitive>&& s)
{
    m_primitives.push_back(std::move(s));
}

