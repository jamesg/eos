#ifndef EOS_RAY_HPP
#define EOS_RAY_HPP

#include <Eigen/Core>

namespace eos
{
    /*!
     * \brief A ray of light or a view ray, with an origin point and direction.
     *
     * \todo Store the direction as a quaternion.
     */
    class ray
    {
    public:
        ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction);

        Eigen::Vector3d origin() const;
        /*!
         * \brief Get a normalised direction vector.
         */
        Eigen::Vector3d direction() const;

        void set_origin(Eigen::Vector3d origin);
        void set_direction(Eigen::Vector3d direction);
    private:
        Eigen::Vector3d m_start, m_direction;
    };
}
#endif

