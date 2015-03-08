#include "sampling.hpp"

#include <cstdlib>

std::vector<Eigen::Vector2d> eos::sample16(
        const double range,
        const double randomness
        )
{
    std::vector<Eigen::Vector2d> out;
    for(int ir = 0; ir < 16; ++ir)
    {
        out.push_back(
            Eigen::Vector2d{
                range * (
                    ir/4 - 1.5 +
                    (((double)std::rand()/RAND_MAX) - 0.5)*randomness
                    ),
                range * (
                    ir%4 - 1.5 +
                    (((double)std::rand()/RAND_MAX) - 0.5)*randomness
                    )
            }
            );
    }
    return out;
}

std::vector<Eigen::Vector3d> eos::sample8(
        const double range,
        const double randomness
        )
{
    std::vector<Eigen::Vector3d> out;
    for(int ir = 0; ir < 8; ++ir)
    {
        out.push_back(
            Eigen::Vector3d{
                range * (
                    ir/4 - 1 +
                    (((double)std::rand()/RAND_MAX) - 0.5)*randomness
                    ),
                range * (
                    (ir%4)/2 - 1 +
                    (((double)std::rand()/RAND_MAX) - 0.5)*randomness
                    ),
                range * (
                    ir%4 - 1 +
                    (((double)std::rand()/RAND_MAX) - 0.5)*randomness
                    )
            }
            );
    }
    return out;
}

