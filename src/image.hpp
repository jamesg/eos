#ifndef EOS_IMAGE_HPP
#define EOS_IMAGE_HPP

#include <ostream>

#include "raytracer.hpp"

namespace eos
{
    class image
    {
    public:
        image(int width, int height);
        void set(Eigen::Vector2i loc, pixel p);
        void operator<<(std::ostream&) const;
    private:
        Eigen::Matrix<pixel, Eigen::Dynamic, Eigen::Dynamic> m_data;
    };
}

#endif

