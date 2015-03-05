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
        std::vector<Eigen::Vector3d> ray_origin() const override;

        void set_softness(double);
    private:
        double m_softness;
    };
}

#endif

