#ifndef EOS_LAMP_HPP
#define EOS_LAMP_HPP

#include <Eigen/Core>

#include "attributes.hpp"

namespace eos
{
    class lamp : public attributes, public has_centre
    {
    public:
        lamp();

        double brightness() const;
        void set_brightness(double brightness);

        /*!
         * \brief Select an origin point for a ray starting at this lamp.
         *
         * \note Depending on the type of lamp, this point may change between
         * invocations.
         */
        virtual Eigen::Vector3d ray_origin() const = 0;

        /*!
         * \brief Recommended number of rays to cast from this lamp.
         *
         * Some lamps use multiple rays to provide softer lighting.  The number
         * of rays should be at least 1.  More rays require more processing
         * time, a sensible maximum is 100.
         */
        virtual int ray_count() const;
    private:
        double m_brightness;
        Eigen::Vector3d m_centre;
    };
}

#endif

