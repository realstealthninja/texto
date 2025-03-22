#include <algorithm>
#include <array>
#include <texto-math/mat.h>

template <size_t W, size_t H, typename T>
mat<W, H, T> mat<W, H, T>::IDENTITY() {
    std::array<std::array<T, H>, W> _mat{};
    
    for (size_t i = 0; i < H; i++) {
        for (size_t j = 0; j < W; j++) {
            _mat.at(i).at(j) = (i == j) ? 1 : 0;
        }
    }
    return mat<W, H, T>(_mat);
}

template <size_t W, size_t H, typename T>
mat<W, H, T> mat<W, H, T>::ZERO() {
    std::array<std::array<T, H>, W> _mat{};

    for (size_t i = 0; i < H; i++) {
        std::fill(_mat.begin(), _mat.end(), 0);
    }
    
    return mat<W, H, T>(_mat);
}

template <size_t W, size_t H, typename T>
T& mat<W, H, T>::operator[](size_t row, size_t col) {
    return _mat.at(row).at(col);
}

template <size_t W, size_t H, typename T>
mat<H, W, T> mat<W, H, T>::transpose() {
    mat<H, W, T> res = mat<H, W, T>::ZERO();

    for(size_t i = 0; i < H; i++) {
        for (size_t j = 0; j < W; j++) {
            res[j, i] = this[i, j];
        }
    }
}