#include "scene.hpp"

#include <algorithm>

eos::pixel eos::scene::background_colour() const
{
    return pixel({0, 0, 0});
}

eos::pixel eos::scene::compute_colour(ray view_ray, int recursions) const
{
    auto distance = [this, view_ray](const sphere& s) {
        return (s.closest_intersection(view_ray) - view_ray.start).norm();
    };
    auto cmp = [distance](const sphere& s1, const sphere& s2) {
        return distance(s1) < distance(s2);
    };
    auto not_in_line = [distance, view_ray](const sphere& s) {
        return !s.intersects(view_ray);
    };

    std::vector<sphere> spheres(m_spheres);
    std::sort(spheres.begin(), spheres.end(), cmp);
    spheres.erase(std::remove_if(spheres.begin(), spheres.end(), not_in_line));

    if(spheres.size() == 0)
        return background_colour();

    pixel out = background_colour();

    auto intersection = spheres.first().closest_intersection(view_ray);

    for(lamp l : m_lamps)
    {
        ray light_ray;
        light_ray.start = l.centre;
        light_ray.direction = intersection - l.centre;
        float len = light_ray.direction.norm();
        // TODO
    }

    return out;
}

