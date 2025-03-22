#ifndef LIBTEXTO_MATH_MAT_H
#define LIBTEXTO_MATH_MAT_H

#include <array>
#include <cstddef>

template <size_t W, size_t H, typename T = float>
class mat {
private:
    std::array<std::array<T, H>, W> _mat{};

public:
    mat(const std::array<std::array<T, H>, W> arr) : mat(arr) {};

    /**
     * @brief Returns and identity matrix
     * 
     * @return mat<W, H, T> 
     */
    static mat<W, H, T> IDENTITY();

    /**
     * @brief Returns a zero matrix
     * 
     * @return mat<W, H, T> 
     */
    static mat<W, H, T> ZERO();

    /**
     * @brief Zero indexed access to the underlying array
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    T& operator[](size_t row, size_t col);
    
    /**
     * @brief One indexed access to the underlying array
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    T& operator()(size_t row, size_t col);

    mat<H, W, T> transpose();
};


#endif // LIBTEXTO_MATH_MAT_H
