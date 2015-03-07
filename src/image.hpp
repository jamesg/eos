#ifndef EOS_IMAGE_HPP
#define EOS_IMAGE_HPP

#include <ostream>

#include "colour.hpp"

namespace eos
{
    class image
    {
    public:
        image(int width, int height);

        int width() const;
        int height() const;

        void set(Eigen::Vector2i, colour::rgb);
        friend std::ostream& operator<<(std::ostream&, const image&);
    private:
        Eigen::Matrix<colour::rgb, Eigen::Dynamic, Eigen::Dynamic> m_data;
    };
    std::ostream& operator<<(std::ostream&, const eos::image&);
}

#endif

