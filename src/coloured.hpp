#ifndef EOS_COLOURED_HPP
#define EOS_COLOURED_HPP

#include "primitive.hpp"

namespace eos
{
    class coloured : public virtual primitive
    {
    public:
        coloured();
        coloured(const colour::rgba colour);

        colour::rgba colour() const override;
        void set_colour(const colour::rgba colour);

    private:
        colour::rgba m_colour;
    };
}

#endif

