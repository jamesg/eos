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
        /*!
         * \brief Compute the final colour for the given view ray.
         */
        pixel compute_colour(const ray&) const;

        /*!
         * \brief Add a lamp to the scene.  The scene takes ownership of the
         * lamp.
         */
        void add(std::unique_ptr<lamp>&&);
        /*!
         * \brief Add a primitive to the scene.  The scene takes ownership of
         * the primitive.
         */
        void add(std::unique_ptr<primitive>&&);
    private:
        /*!
         * \brief Compute the list of primitives visible along the view ray
         * ordered by distance from the origin of the view ray.
         */
        std::vector<const primitive*> visible(ray) const;
        pixel compute_colour(ray, int recursions) const;
        pixel background_colour() const;

        std::vector<std::unique_ptr<lamp>> m_lamps;
        std::vector<std::unique_ptr<primitive>> m_primitives;
    };
}

#endif

