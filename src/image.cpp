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

    auto limit_channel = [](const double p) -> int {
        return std::max(0.0, std::min(1.0, p)) * 255;
    };
    for(int ih = 0; ih < img.height(); ++ih)
        for(int iw = 0; iw < img.width(); ++iw)
            os << limit_channel(img.m_data(ih, iw)[0]) << " " <<
                limit_channel(img.m_data(ih, iw)[1]) << " " <<
                limit_channel(img.m_data(ih, iw)[2]) << std::endl;
    return os;
}

