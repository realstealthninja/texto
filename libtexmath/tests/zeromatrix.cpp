#define CATCH_CONFIG_MAIN
#include <texmath/mat.h>
#include <catch2/catch_test_macros.hpp>
using namespace texmath;

TEST_CASE("Zero matrix is zero matrix", "[matrix]") {
    auto zero_matrix = mat<3, 3>::ZERO();

    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            REQUIRE(zero_matrix[i, j] == 0.0f);
        }
    } 
}

TEST_CASE("Transpose of a zero matrix is still a zero matrix", "[matrix]") {
    auto zero_matrix = mat<3, 3>::ZERO();
    zero_matrix = zero_matrix.transpose();

    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 3; j++) {
            REQUIRE(zero_matrix[i, j] == 0.0f);
        }
    } 
}

TEST_CASE(
    "Transpose of a non square zero matrix",
    "[matrix]"
) {
    mat<3, 2> zero_mat = mat<3, 2>::ZERO();
    mat<2, 3> zero_mat_t = zero_mat.transpose();


    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            REQUIRE(zero_mat_t[i, j] == 0.0f);
        }
    }

}
