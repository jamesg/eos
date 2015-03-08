#include "colour.hpp"

eos::colour::rgb eos::colour::to_rgb(const rgba& c)
{
    return c.block<3, 1>(0, 0);
}

eos::colour::rgba eos::colour::to_rgba(const rgb& c)
{
    rgba out;
    out << c, 1.0;
    return out;
}

eos::colour::rgba eos::colour::over(const rgba a, const rgba b)
{
    // 'over' operator
    // C_o = C_a * A_a + C_b * A_b * (1 - A_a)
    // A_o = (c_o / C_o) = A_a + (A_b * (1- A_a))
    rgba out;
    out <<
        a.block<3, 1>(0, 0) * a[3] + b.block<3, 1>(0, 0) * b[3] * (1 - a[3]),
        a[3] + b[3] * (1 - a[3]);
    return out;
}

eos::colour::rgba eos::colour::over_assoc(const rgba a, const rgba b)
{
    if(a[3] == 0.0 && b[3] == 0.0)
        return colour::rgba(0.0, 0.0, 0.0, 0.0);
    rgba out;
    out <<
        (1.0 / (a[3] + b[3] * (1 - a[3]))) * (
                a.block<3, 1>(0, 0) * a[3] +
                b.block<3, 1>(0, 0) * b[3] * (1 - a[3])
                ),
        a[3] + b[3] * (1 - a[3]);
    return out;
}

