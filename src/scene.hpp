#ifndef EOS_SCENE_HPP
#define EOS_SCENE_HPP

#include <memory>

#include "pixel.hpp"
#include "primitive.hpp"

namespace eos
{
    class ray;

    class scene
    {
    public:
        pixel compute_colour(const ray&) const;

        void add(std::unique_ptr<lamp>&&);
        void add(std::unique_ptr<primitive>&&);
    private:
        pixel compute_colour(ray, int recursions) const;
        pixel background_colour() const;

        std::vector<std::unique_ptr<lamp>> m_lamps;
        std::vector<std::unique_ptr<primitive>> m_primitives;
    };
}

#endif

