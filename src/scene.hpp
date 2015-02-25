#ifndef EOS_SCENE_HPP
#define EOS_SCENE_HPP

#include "raytracer.hpp"
#include "sphere.hpp"

namespace eos
{
    class scene
    {
    public:
        pixel compute_colour(ray, int recursions) const;
        pixel background_colour() const;
    private:
        std::vector<lamp> m_lamps;
        std::vector<sphere> m_spheres;
    };
}

#endif

