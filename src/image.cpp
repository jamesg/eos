#include "image.hpp"

eos::image::image(int width, int height) :
    m_data(height, width)
{
}

int eos::image::width() const
{
    return m_data.cols();
}

int eos::image::height() const
{
    return m_data.rows();
}

void eos::image::set(Eigen::Vector2i loc, pixel p)
{
    m_data(loc[1], loc[0]) = p;
}

std::ostream& eos::operator<<(std::ostream& os, const eos::image& img)
{
    os << "P3" << std::endl;
    os << img.width() << " " << img.height() << std::endl;
    os << "255" << std::endl;
    for(int ih = 0; ih < img.height(); ++ih)
        for(int iw = 0; iw < img.width(); ++iw)
            os << (int)(img.m_data(ih, iw)[0]*255.0) << " " <<
                (int)(img.m_data(ih, iw)[1]*255.0) << " " <<
                (int)(img.m_data(ih, iw)[2]*255.0) << std::endl;
    return os;
}

