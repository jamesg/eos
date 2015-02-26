#include "catch.hpp"

#include <Eigen/Geometry>
#include "ray.hpp"
#include "triangle.hpp"

SCENARIO("eos::triangle") {
    GIVEN("a triangle with points at (0, 0), (0, 1) and (1, 0) in the y plane") {
        eos::triangle t(
                Eigen::Vector3d(0.0, 0.0, 1.0),
                Eigen::Vector3d(0.0, 0.0, 0.0),
                Eigen::Vector3d(1.0, 0.0, 0.0)
                );

        THEN("line (1, 0, 1) -> (0, 1, 0) does not intersect") {
            eos::ray light_ray(
                    Eigen::Vector3d(1.0, 0.0, 1.0),
                    Eigen::Vector3d(0.0, 1.0, 0.0)
                    );
            REQUIRE(!t.intersects(light_ray));
        }

        THEN("line (10, 0, 10) -> (0, 1, 0) does not intersect") {
            eos::ray light_ray(
                    Eigen::Vector3d(10.0, 0.0, 10.0),
                    Eigen::Vector3d(0.0, 1.0, 0.0)
                    );
            REQUIRE(!t.intersects(light_ray));
        }

        THEN("line (0.25, 0, 0.25) -> (0, 1, 0) does intersect") {
            eos::ray light_ray(
                    Eigen::Vector3d(0.25, 0.0, 0.25),
                    Eigen::Vector3d(0.0, 1.0, 0.0)
                    );
            REQUIRE(t.intersects(light_ray));
        }
    }
}

