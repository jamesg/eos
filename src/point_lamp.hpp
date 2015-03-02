#ifndef EOS_POINT_LAMP_HPP
#define EOS_POINT_LAMP_HPP

#include "lamp.hpp"

namespace eos
{
    /*!
     * \brief Simple light source that always originates rays from the same
     * point.
     */
    class point_lamp : public lamp
    {
    public:
        Eigen::Vector3d ray_origin() const override;
    };
}

#endif

