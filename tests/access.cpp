#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <texmath/mat.h>

texmath::mat<3, 3> matrix = {
    {1.0f , 2.0f , 3.0f},
    {-2.0f, -5.0f, 3.0f},
    {10.0f, 1.0f, 0.5f}
};

TEST_CASE("Invalid access into matrix via () operator", "[matrix]") {
    REQUIRE_THROWS_AS(matrix(0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(4, 4), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(4, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(3, 4), std::invalid_argument);
}

TEST_CASE("Invalid access into matrix via [] operator", "[matrix]") {
    REQUIRE_THROWS_AS((matrix[4, 4]), std::invalid_argument);
    REQUIRE_THROWS_AS((matrix[4, 3]), std::invalid_argument);
    REQUIRE_THROWS_AS((matrix[3, 4]), std::invalid_argument);
}
