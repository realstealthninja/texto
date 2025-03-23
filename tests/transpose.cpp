#include <catch2/catch_test_macros.hpp>
#include <texto-math/mat.h>

TEST_CASE("Fixed transpose on a square matrix", "[matrix]") {
    std::array<std::array<int, 3>, 3> mat_arr(
        {
            std::array<int, 3>({3, 9, 8}),
            std::array<int, 3>({2, 7, 6}),
            std::array<int, 3>({1, 5, 4})
        }
    );
    mat<3, 3, int> mat1(mat_arr);
    REQUIRE(mat1.is_square());
    mat<3, 3, int> mat1_transposed = mat1.transpose();
    REQUIRE(mat1_transposed.is_square());

    //  ┌           ┐T      ┌           ┐
    //  │  3  9  8  │       │  3  2  1  │ 
    //  │  2  7  6  │   =   │  9  7  5  │
    //  │  1  5  4  │       │  8  6  4  │
    //  └           ┘       └           ┘
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            REQUIRE(mat1[i, j] == mat1_transposed[j, i]);
        }
    }
}

TEST_CASE("Fixed transpose on a non square matrix", "[matrix]") {
    std::array<std::array<int, 3>, 3> mat_arr(
        {
            std::array<int, 3>({3, 9}),
            std::array<int, 3>({2, 7}),
            std::array<int, 3>({1, 5})
        }
    );
    mat<3, 3, int> mat1(mat_arr);
    mat<3, 3, int> mat1_transposed = mat1.transpose();

    //  ┌        ┐T      ┌           ┐
    //  │  3  9  │       │  3  2  1  │ 
    //  │  2  7  │   =   │  9  7  5  │
    //  │  1  5  │       └           ┘
    //  └        ┘ 

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            REQUIRE(mat1[i, j] == mat1_transposed[j, i]);
        }
    }
}