#ifndef EOS_SCENE_HPP
#define EOS_SCENE_HPP

#include <memory>

#include "colour.hpp"
#include "image.hpp"
#include "primitive.hpp"

namespace eos
{
    class ray;

    class scene
    {
    public:
        scene();

        /*!
         * \brief Compute the final colour for the given view ray.
         */
        colour::rgb compute_colour(const ray&) const;

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
        image render(int width, int height) const;

        void set_camera_distance(double);
        void set_camera_apeture(double);
    private:
        /*!
         * \brief Compute the list of primitives visible along the view ray
         * ordered by distance from the origin of the view ray.
         */
        std::vector<const primitive*> visible(ray) const;
        colour::rgba compute_colour(ray, int recursions) const;
        colour::rgb background_colour() const;

        std::vector<std::unique_ptr<lamp>> m_lamps;
        std::vector<std::unique_ptr<primitive>> m_primitives;

        double m_distance;
        double m_apeture;
    };
}

#endif

