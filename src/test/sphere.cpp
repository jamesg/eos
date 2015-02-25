#include "catch.hpp"

#include "sphere.hpp"

SCENARIO("eos::sphere") {
    GIVEN("a sphere radius 1.0 at (0, 0, 0)") {
        eos::sphere s;
        s.radius = 1.0;
        s.centre = {0.0, 0.0, 0.0};

        THEN("ray (-1, -1, -1) -> (1, 1, 1) intersects") {
            eos::ray light_ray;
            light_ray.start = {-1.0, -1.0, -1.0};
            light_ray.direction = {1.0, 1.0, 1.0};
            REQUIRE(s.intersects(light_ray));
        }

        THEN("ray (-2, -1, -1) -> (0, 1, 0) does not intersect") {
            eos::ray light_ray;
            light_ray.start = {-2.0, -1.0, -1.0};
            light_ray.direction = {0.0, 1.0, 0.0};
            REQUIRE(!s.intersects(light_ray));
        }

        THEN("ray (-2, 0, 0) -> (1, 0, 0) intersects at (-1, 0, 0)") {
            eos::ray light_ray;
            light_ray.start = {-2.0, 0.0, 0.0};
            light_ray.direction = {1.0, 0.0, 0.0};
            REQUIRE(s.intersects(light_ray));
            Eigen::Vector3f intersection = s.closest_intersection(light_ray);
            CHECK(intersection[0] == -1.0);
            CHECK(intersection[1] == 0.0);
            CHECK(intersection[2] == 0.0);
        }
    }
}

