#ifndef EOS_MATERIAL_HPP
#define EOS_MATERIAL_HPP

#include "primitive.hpp"

namespace eos
{
    /*!
     * \brief Give a primitive some basic material attributes.
     */
    class material : public virtual primitive
    {
    public:
        material();
        material(double reflectivity, double specvalue, double specpower);

        double reflectivity() const;
        double specvalue() const;
        double specpower() const;

        void set_reflectivity(double reflectivity);
        void set_specvalue(double specvalue);
        void set_specpower(double specpower);

        void set_material_attributes(
                double reflectivity,
                double specvalue,
                double specpower
                );

    private:
        double m_reflectivity, m_specvalue, m_specpower;
    };
}

#endif

