#ifndef EOS_IMAGE_HPP
#define EOS_IMAGE_HPP

#include <ostream>

#include "pixel.hpp"

namespace eos
{
    class image
    {
    public:
        image(int width, int height);

        int width() const;
        int height() const;

        void set(Eigen::Vector2i loc, pixel p);
        friend std::ostream& operator<<(std::ostream&, const image&);
    private:
        Eigen::Matrix<pixel, Eigen::Dynamic, Eigen::Dynamic> m_data;
    };
    std::ostream& operator<<(std::ostream&, const eos::image&);
}

#endif

