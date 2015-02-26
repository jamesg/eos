#include "scene.hpp"

#include <algorithm>
#include <iostream>

#include "ray.hpp"

eos::pixel eos::scene::background_colour() const
{
    return pixel({0, 0, 0});
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

    std::vector<const primitive*> primitives;
    std::transform(
            m_primitives.begin(),
            m_primitives.end(),
            std::back_inserter(primitives),
            [](const std::unique_ptr<primitive>& p) {
                return p.get();
            }
            );
    primitives.erase(
            std::remove_if(primitives.begin(), primitives.end(), not_in_line),
            primitives.end()
            );

    if(primitives.size() == 0)
        return background_colour();

    std::sort(primitives.begin(), primitives.end(), cmp);

    pixel out = background_colour();

    const primitive *closest = primitives.at(0);
    auto intersection = closest->closest_intersection(view_ray);

    for(lamp current_lamp : m_lamps)
    {
        // lamp -> intersection
        ray light_ray(current_lamp.centre, intersection - current_lamp.centre);

        auto in_line = [&closest, light_ray](
                const std::unique_ptr<primitive>& shape
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
            return (lamp_closest < lamp_shape);
        };

        // Find objects along the line from the lamp to the object.  If there
        // are objects along this line, there will be a shadow on the object.
        if(
            std::find_if(
                m_primitives.begin(),
                m_primitives.end(),
                in_line
                ) == m_primitives.end()
          )
            out += closest->diffuse(current_lamp, view_ray);
    }

    return out;
}

void eos::scene::add(const lamp& l)
{
    m_lamps.push_back(l);
}

void eos::scene::add(std::unique_ptr<primitive>&& s)
{
    m_primitives.push_back(std::move(s));
}

