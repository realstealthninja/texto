#include "catch2/catch_test_macros.hpp"
#include <texto-math/mat.h>

TEST_CASE("Additon of two matrices", "[matrix]") {
    std::array<std::array<int, 3>, 3> mat1_arr(
        {
            std::array<int, 3>({3, 9, 8}),
            std::array<int, 3>({2, 7, 6}),
            std::array<int, 3>({1, 5, 4})
        }
    );

    mat<3, 3, int> mat1(mat1_arr);

    std::array<std::array<int, 3>, 3> mat2_arr(
        {
            std::array<int, 3>({2, -1, 2}),
            std::array<int, 3>({2, 7, 3}),
            std::array<int, 3>({0, -3, 0})
        }
    );

    mat<3, 3, int> mat2(mat2_arr);

    std::array<std::array<int, 3>, 3> resmat_arr(
        {
            std::array<int, 3>({5, 8, 10}),
            std::array<int, 3>({4, 14, 9}),
            std::array<int, 3>({1, 2, 4})
        }
    );

    mat<3, 3, int> resmat = mat1 + mat2;

    
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            REQUIRE(resmat[i, j] == resmat_arr.at(i).at(j)); 
        }
    }

}