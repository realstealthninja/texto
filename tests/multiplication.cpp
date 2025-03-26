#include <catch2/catch_test_macros.hpp>
#include <texmath/mat.h>
using namespace texmath;

TEST_CASE("Multiplication with zero matrix", "[matrix]") {
    auto mat1 = mat<3, 3>::ZERO();
    std::array<std::array<float, 3>, 3> mat_arr(
        {
            std::array<float, 3>({3, 9, 8}),
            std::array<float, 3>({2, 7, 6}),
            std::array<float, 3>({1, 5, 4})
        }
    );
    mat<3, 3> mat2(mat_arr);

    auto res = mat1 * mat2;

    REQUIRE(res == mat1);
}

TEST_CASE("Multiplication with Identity matrix", "[matrix]") {
    auto mat1 = mat<3, 3>::IDENTITY();
    std::array<std::array<float, 3>, 3> mat_arr(
        {
            std::array<float, 3>({3, 9, 8}),
            std::array<float, 3>({2, 7, 6}),
            std::array<float, 3>({1, 5, 4})
        }
    );
    mat<3, 3> mat2(mat_arr);

    auto res = mat1 * mat2;

    REQUIRE(res == mat2);
}
