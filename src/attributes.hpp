#ifndef EOS_ATTRIBUTES_HPP
#define EOS_ATTRIBUTES_HPP

#include <Eigen/Core>

namespace eos
{
    /*!
     * \brief Base class for all attribute types to inherit from.
     */
    class attributes
    {
    public:
        // 'attributes' needs to be a polymorphic type.
        virtual ~attributes();
    };

    /*!
     * \brief A type that has x, y, z coordinates representing the centre.
     */
    class has_centre
    {
    public:
        has_centre();
        has_centre(Eigen::Vector3d);
        Eigen::Vector3d centre() const;
        void set_centre(Eigen::Vector3d centre);
    private:
        Eigen::Vector3d m_centre;
    };
}

#endif

