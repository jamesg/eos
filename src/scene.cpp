#include "scene.hpp"

#include <algorithm>
#include <cstdlib>

#include "colour.hpp"
#include "lamp.hpp"
#include "ray.hpp"
#include "sampling.hpp"

eos::scene::scene() :
    m_distance(3000.0),
    m_apeture(0.0)
{
}

eos::colour::rgb eos::scene::background_colour() const
{
    return colour::rgb(1, 0, 1);
}

eos::colour::rgba eos::scene::compute_colour(const ray& view_ray) const
{
    return colour::over(
            compute_colour(view_ray, 2),
            colour::to_rgba(background_colour())
            );
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

eos::colour::rgba eos::scene::compute_colour(ray view_ray, int recursions) const
{
    view_ray.set_origin(view_ray.origin() + view_ray.direction());

    std::vector<const primitive*> primitives(visible(view_ray));

    if(primitives.size() == 0)
        return colour::rgba(0.0, 0.0, 0.0, 0.0);

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

    return blend(
        m_lamps.begin(),
        m_lamps.end(),
        [this, closest, &in_ray, &intersection, &view_ray, recursions](
            const std::unique_ptr<lamp>& current_lamp
            )
        {
            std::vector<Eigen::Vector3d> ray_origins(current_lamp->ray_origin());
            if(ray_origins.empty())
                return colour::rgba(0.0, 0.0, 0.0, 1.0);

            colour::rgba reflected(0.0, 0.0, 0.0, 0.0);
            if(recursions > 1)
            {
                Eigen::Vector3d normal =
                    closest->normal(intersection).normalized();
                // If the normal is in the wrong direction.
                if(normal.dot(-view_ray.direction()) < 0)
                    normal = -normal;
                auto out_ray_dir =
                    normal + (normal - (-view_ray.direction()));
                ray out_ray(intersection, out_ray_dir);
                colour::rgba p = compute_colour(out_ray, recursions - 1);
                reflected = p;// * closest->reflectivity();
            }

            return colour::over(
                reflected,
                blend(
                    ray_origins.begin(),
                    ray_origins.end(),
                    [this, closest, &current_lamp, &in_ray, &intersection, &view_ray](
                        const Eigen::Vector3d& origin
                        )
                    {
                        // lamp -> intersection
                        ray light_ray(origin, intersection - origin);

                        // Find objects along the line from the lamp to the object.
                        // If there are objects along this line, there will be a
                        // shadow on the object.
                        return (
                            std::find_if(
                                m_primitives.begin(),
                                m_primitives.end(),
                                std::bind(in_ray, std::placeholders::_1, light_ray)
                                ) == m_primitives.end()
                          )?
                            colour::to_rgba(closest->diffuse(*current_lamp, view_ray)):
                            colour::rgba(0.0, 0.0, 0.0, 1.0);
                    }
                    )
                );
        }
        );
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
            Eigen::Vector3d screen{
                double(ix - output.width()/2),
                -200,
                double(iy - output.height()/2)
            };
            const double RANDOMNESS = 1.0;
            std::vector<Eigen::Vector2d> samples =
                sample16(m_apeture, RANDOMNESS);
            colour::rgba c = eos::blend(
                    samples.begin(),
                    samples.end(),
                    [this, screen](const Eigen::Vector2d& sample) {
                        Eigen::Vector3d apeture{
                            sample[0],
                            -m_distance,
                            sample[1]
                        };
                        ray view_ray(apeture, screen - apeture);
                        return compute_colour(view_ray);
                    }
                    );
            output.set({ix, iy}, colour::to_rgb(c));
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

