#ifndef EOS_PRIMITIVE_HPP
#define EOS_PRIMITIVE_HPP

#include <memory>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "attributes.hpp"
#include "colour.hpp"

namespace eos
{
    class lamp;
    class ray;

    /*!
     * \brief Interface describing a primitive shape that can interact with
     * light rays.
     */
    class primitive : public attributes
    {
    public:
        typedef Eigen::Transform<double, 3, Eigen::Projective> transform_type;

        virtual colour::rgba colour() const;
        virtual double reflectivity() const;
        /*!
         * \brief Render a point on the surface under diffuse lighting.
         *
         * Brightness is computed by Lambertian reflectance.
         */
        colour::rgba diffuse(const lamp&, const ray& view_ray) const;
        /*!
         * \brief Check whether a light ray intersects with the object.
         */
        virtual bool intersects(const ray& light_ray) const = 0;
        /*!
         * \brief Find the closest point at which the light ray intersects the
         * object.
         *
         * \throws std::exception if the ray does not intersect the object.
         */
        virtual Eigen::Vector3d
            closest_intersection(const ray& light_ray) const = 0;
        /*!
         * \brief Find the direction of the normal at a point.
         *
         * \note This may be undefined if the point has not been returned as
         * closest_intersection.
         */
        virtual Eigen::Vector3d normal(Eigen::Vector3d) const = 0;
        /*!
         * \brief Transform the primitive by a transformation matrix.
         */
        virtual void transform(transform_type) = 0;
    };
}

#endif

