#define CATCH_CONFIG_MAIN
#include <texto-math/mat.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Zero matrix is zero matrix", "[matrix]") {
    auto matrix1 = mat<3, 3>::ZERO();

    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            REQUIRE(matrix1[i, j] == 0.0f);
        }
    } 
}