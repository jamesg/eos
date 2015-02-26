#include "triangle.hpp"

#include <stdexcept>

#include <Eigen/Geometry>

#include "ray.hpp"

eos::triangle::triangle(Eigen::Matrix<double, 3, 3> points) :
    m_points(points)
{
}

eos::triangle::triangle(
        Eigen::Vector3d p1,
        Eigen::Vector3d p2,
        Eigen::Vector3d p3
        )
{
    m_points.col(0) = p1;
    m_points.col(1) = p2;
    m_points.col(2) = p3;
}

bool eos::triangle::intersects(const ray& light_ray) const
{
    const auto p0(m_points.col(0));
    const auto p1(m_points.col(1));
    const auto p2(m_points.col(2));

    // t = -( ((o-p).n) / (d.n) )
    // x = o + td

    // Normal from the front.
    auto n = (p1 - p0).cross(p2 - p0);
    // p0 could be any vertex
    auto t = -(
            (light_ray.origin()-p0).dot(n) /
            light_ray.direction().dot(n)
            );
    // x is the point where the light ray intersects the plane.
    const Eigen::Vector3d x = light_ray.origin() + t*light_ray.direction();

    // (p1 - p0) x (x - p0) . n >= 0
    // (p2 - p1) x (x - p1) . n >= 0
    // (p0 - p2) x (x - p2) . n >= 0

    return (
            ((p1 - p0).cross(x - p0)).dot(n) > -01 &&
            ((p2 - p1).cross(x - p1)).dot(n) > -01 &&
            ((p0 - p2).cross(x - p2)).dot(n) > -01
           );
}

Eigen::Vector3d eos::triangle::closest_intersection(const ray& light_ray) const
{
    if(!intersects(light_ray))
        throw std::runtime_error("line does not intersect triangle");

    const auto p0(m_points.col(0));
    const auto p1(m_points.col(1));
    const auto p2(m_points.col(2));

    // t = -( ((o-p).n) / (d.n) )
    // x = o + td

    // Normal from the front.
    auto n = (p1 - p0).cross(p2 - p0);
    // p0 could be any vertex
    auto t = -(
            (light_ray.origin()-p0).dot(n) /
            light_ray.direction().dot(n)
            );
    // x is the point where the light ray intersects the plane.
    auto x = light_ray.origin() + t*light_ray.direction();
    return x;
}

Eigen::Vector3d eos::triangle::normal(Eigen::Vector3d) const
{
    const auto p0(m_points.col(0));
    const auto p1(m_points.col(1));
    const auto p2(m_points.col(2));

    // TODO: may be pointing backward
    auto n = (p1 - p0).cross(p2 - p0);
    return n.normalized();
}

