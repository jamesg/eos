#ifndef EOS_SCENE_HPP
#define EOS_SCENE_HPP

#include <memory>

#include <boost/ptr_container/ptr_vector.hpp>

#include "raytracer.hpp"
#include "primitive.hpp"

namespace eos
{
    class ray;

    class scene
    {
    public:
        pixel compute_colour(const ray&, int recursions) const;

        void add(const lamp&);
        void add(std::unique_ptr<primitive>&&);
    private:
        pixel background_colour() const;

        std::vector<lamp> m_lamps;
        std::vector<std::unique_ptr<primitive>> m_primitives;
    };
}

#endif

