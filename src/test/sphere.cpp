#include "catch.hpp"

#include "ray.hpp"
#include "sphere.hpp"

SCENARIO("eos::sphere") {
    GIVEN("a sphere radius 1.0 at (0, 0, 0)") {
        eos::sphere s;
        s.set_radius(1.0);
        s.set_centre({0.0, 0.0, 0.0});

        THEN("ray (-1, -1, -1) -> (1, 1, 1) intersects") {
            eos::ray light_ray({-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});
            REQUIRE(s.intersects(light_ray));
        }

        THEN("ray (-0.2, -3.0, -0.2) -> (0.0, 1.0, 0.0) intersects") {
            eos::ray light_ray({-0.2, -3.0, -0.2}, {0.0, 1.0, 0.0});
            REQUIRE(s.intersects(light_ray));
        }

        THEN("ray (-2, -1, -1) -> (0, 1, 0) does not intersect") {
            eos::ray light_ray({-2.0, -1.0, -1.0}, {0.0, 1.0, 0.0});
            REQUIRE(!s.intersects(light_ray));
            REQUIRE_THROWS(s.closest_intersection(light_ray));
        }

        THEN("ray (-199, -1000, -149) -> (199, 500, 149) does not intersect") {
            eos::ray light_ray({-199, -1000, -149}, {199, 500, 149});
            REQUIRE(!s.intersects(light_ray));
            REQUIRE_THROWS(s.closest_intersection(light_ray));
        }

        THEN("ray (-2, 0, 0) -> (1, 0, 0) intersects at (-1, 0, 0)") {
            eos::ray light_ray({-2.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
            REQUIRE(s.intersects(light_ray));
            Eigen::Vector3d intersection = s.closest_intersection(light_ray);
            CHECK(intersection[0] == -1.0);
            CHECK(intersection[1] == 0.0);
            CHECK(intersection[2] == 0.0);
        }
    }
}

