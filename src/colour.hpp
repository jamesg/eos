#ifndef EOS_COLOUR_HPP
#define EOS_COLOUR_HPP

#include <Eigen/Core>

namespace eos
{
    namespace colour
    {
        typedef Eigen::Vector3d rgb;
        typedef Eigen::Vector4d rgba;

        rgb to_rgb(const rgba&);
        rgba to_rgba(const rgb&);

        /*!
         * \brief Compute the colour acheived by laying 'a' over 'b'.
         */
        rgba over(const rgba a, const rgba b);
        /*!
         * \brief Compute the colour acheived by laying 'a' over 'b'
         * (associative).
         */
        rgba over_assoc(const rgba a, const rgba b);
    }
}

#endif

