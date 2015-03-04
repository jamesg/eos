#include "scene.hpp"

#include <algorithm>
#include <cstdlib>

#include "lamp.hpp"
#include "ray.hpp"

eos::scene::scene() :
    m_distance(3000.0),
    m_apeture(0.0)
{
}

eos::pixel eos::scene::background_colour() const
{
    return pixel({1, 1, 1});
}

eos::pixel eos::scene::compute_colour(const ray& view_ray) const
{
    return compute_colour(view_ray, 2);
}

std::vector<const eos::primitive*> eos::scene::visible(ray view_ray) const
{
    auto distance = [this, view_ray](const primitive *p) {
        return (p->closest_intersection(view_ray) - view_ray.origin()).norm();
    };
    auto cmp = [distance](const primitive *p1, const primitive *p2) {
        return distance(p1) < distance(p2);
    };
    auto not_in_line = [distance, view_ray](const primitive *p) {
        return !p->intersects(view_ray);
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
    // Sort primitives on the view ray by distance from the camera.
    std::sort(primitives.begin(), primitives.end(), cmp);

    return primitives;
}

eos::pixel eos::scene::compute_colour(ray view_ray, int recursions) const
{
    pixel out({0, 0, 0});

    view_ray.set_origin(view_ray.origin() + view_ray.direction());

    std::vector<const primitive*> primitives(visible(view_ray));

    if(primitives.size() == 0)
        return out;

    const primitive *closest = primitives.at(0);
    auto intersection = closest->closest_intersection(view_ray);

    // Check if 'shape' intersects 'light_ray' between the light ray origin and
    // 'closest'.  In other words, check if primitive 'shape' casts a shadow on
    // 'closest'.
    auto in_ray = [&closest](
            const std::unique_ptr<primitive>& shape,
            const ray& light_ray
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

    for(const std::unique_ptr<lamp>& current_lamp : m_lamps)
    {
        std::vector<Eigen::Vector3d> ray_origins(current_lamp->ray_origin());
        if(ray_origins.empty())
            continue;
        eos::pixel ray_colour(0, 0, 0);
        for(auto origin : ray_origins)
        {
            // lamp -> intersection
            ray light_ray(origin, intersection - origin);

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
                ray_colour += closest->diffuse(*current_lamp, view_ray);
        }
        ray_colour /= ray_origins.size();
        out += ray_colour;
    }

    if(recursions > 1)
    {
        Eigen::Vector3d normal = closest->normal(intersection).normalized();
        // If the normal is in the wrong direction.
        if(normal.dot(-view_ray.direction()) < 0)
            normal = -normal;
        auto out_ray_dir =
            normal + (normal - (-view_ray.direction()));
        ray out_ray(intersection, out_ray_dir);
        pixel p = compute_colour(out_ray, recursions - 1);
        out += p * closest->reflectivity();
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

eos::image eos::scene::render(const int width, const int height) const
{
    image output(width, height);
    for(int ix = 0; ix < output.width(); ++ix)
    {
        for(int iy = 0; iy < output.height(); ++iy)
        {
            pixel c({0.0, 0.0, 0.0});
            for(int ir = 0; ir < 4; ++ir)
            {
                Eigen::Vector3d screen{
                    (float(ix) - output.width()/2),
                    -200,
                    (float(iy) - output.height()/2)
                };
                Eigen::Vector3d apeture{
                    m_apeture * (ir/2 + ((double)std::rand()/RAND_MAX) - 1.0),
                    -m_distance,
                    m_apeture * (ir%2 + ((double)std::rand()/RAND_MAX) - 1.0),
                };
                ray view_ray(apeture, screen - apeture);
                c += compute_colour(view_ray) / 4;
            }
            output.set({ix, iy}, c);
        }
    }
    return output;
}

void eos::scene::set_camera_distance(double distance)
{
    m_distance = distance;
}

void eos::scene::set_camera_apeture(double apeture)
{
    m_apeture = apeture;
}

