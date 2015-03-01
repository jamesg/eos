#ifndef EOS_COLOURED_HPP
#define EOS_COLOURED_HPP

#include "primitive.hpp"

namespace eos
{
    class coloured : public virtual primitive
    {
    public:
        coloured();
        coloured(const pixel colour);

        pixel colour() const override;
        void set_colour(const pixel colour);

    private:
        pixel m_colour;
    };
}

#endif

