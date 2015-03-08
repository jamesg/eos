#ifndef EOS_SAMPLING_HPP
#define EOS_SAMPLING_HPP

#include <algorithm>
#include <vector>

#include <Eigen/Core>

#include "colour.hpp"

namespace eos
{
    std::vector<Eigen::Vector2d> sample16(
            const double range,
            const double randomness
            );

    std::vector<Eigen::Vector3d> sample8(
            const double range,
            const double randomness
            );

    template<typename Iterator, typename Function>
    colour::rgba blend(Iterator begin, Iterator end, Function f)
    {
        std::vector<colour::rgba> colours;
        std::transform(begin, end, std::back_inserter(colours), f);
        colour::rgba out = std::accumulate(
                colours.begin(),
                colours.end(),
                colour::rgba(0.0, 0.0, 0.0, 0.0)
                );
        out /= std::distance(begin, end);
        return out;
    }
}

#endif

