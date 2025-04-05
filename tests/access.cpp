#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <texmath/mat.h>


TEST_CASE("Valid access into matrix via () operator", "[matrix]") {
    std::array<std::array<float, 3>, 3> hello {
        std::array<float, 3> {  1.0f,  2.0f, 3.0f},
        std::array<float, 3> { -2.0f, -5.0f, 3.0f},
        std::array<float, 3> { 10.0f,  1.0f, 0.5f}
        };
    texmath::mat<3, 3, float> mat_123(hello);

    REQUIRE(mat_123(1,1) == 1.0f);
    REQUIRE(mat_123(3, 3) == 0.5f);
    REQUIRE(mat_123(3, 2) == 1.0f);
    REQUIRE(mat_123(2, 3) == 3.0f);
}

TEST_CASE("Valid access into matrix via [] operator", "[matrix]") {
    texmath::mat<3, 3> matrix = {
    {  1.0f,  2.0f, 3.0f},
    { -2.0f, -5.0f, 3.0f},
    { 10.0f,  1.0f, 0.5f}
    };


    bool statement = matrix[0, 0] == 1.0f;
    REQUIRE(statement);
    REQUIRE((matrix[2, 2]) == 0.5f);
    REQUIRE((matrix[2, 1]) == 1.0f);
    REQUIRE((matrix[1, 2]) == 3.0f);
}



TEST_CASE("Invalid access into matrix via () operator", "[matrix]") {
    texmath::mat<3, 3> matrix = {
    {  1.0f,  2.0f, 3.0f},
    { -2.0f, -5.0f, 3.0f},
    { 10.0f,  1.0f, 0.5f}
    };
    REQUIRE_THROWS_AS(matrix(0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(4, 4), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(4, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(matrix(3, 4), std::invalid_argument);
}

TEST_CASE("Invalid access into matrix via [] operator", "[matrix]") {
    texmath::mat<3, 3> matrix = {
    {  1.0f,  2.0f, 3.0f},
    { -2.0f, -5.0f, 3.0f},
    { 10.0f,  1.0f, 0.5f}
    };
    REQUIRE_THROWS_AS((matrix[4, 4]), std::invalid_argument);
    REQUIRE_THROWS_AS((matrix[4, 3]), std::invalid_argument);
    REQUIRE_THROWS_AS((matrix[3, 4]), std::invalid_argument);
}
