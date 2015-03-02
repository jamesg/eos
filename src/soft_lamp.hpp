#ifndef EOS_SOFT_LAMP_HPP
#define EOS_SOFT_LAMP_HPP

#include "lamp.hpp"

namespace eos
{
    /*!
     * \brief Provide soft lighting by randomly distributing rays across a flat
     * surface.
     */
    class soft_lamp : public lamp
    {
    public:
        soft_lamp();
        /*!
         * \brief Cast a ray from a random point on the lamp's surface.
         */
        Eigen::Vector3d ray_origin() const override;
        int ray_count() const override;

        Eigen::Vector3d normal() const;
        void set_normal(Eigen::Vector3d);
    private:
        Eigen::Vector3d m_normal;
    };
}

#endif

