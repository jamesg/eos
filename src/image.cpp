#include "image.hpp"

eos::image::image(int width, int height) :
    m_data(height, width)
{
}

void eos::image::set(Eigen::Vector2i loc, pixel p)
{
    m_data(loc[0], loc[1]) = p;
}

void eos::image::operator<<(std::ostream& os) const
{
    os << "P3" << std::endl;
    os << m_data.cols() << " " << m_data.rows() << std::endl;
    os << "255" << std::endl;
    for(int ih = 0; ih < m_data.rows(); ++ih)
        for(int iw = 0; iw < m_data.cols(); ++iw)
            os << m_data(ih, iw)[0] << " " <<
                m_data(ih, iw)[1] << " " <<
                m_data(ih, iw)[2] << std::endl;
}

