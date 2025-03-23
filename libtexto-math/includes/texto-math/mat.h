#ifndef LIBTEXTO_MATH_MAT_H
#define LIBTEXTO_MATH_MAT_H

#include <array>
#include <cassert>
#include <cstddef>

/**
 * @brief A templated matrix class able to represent a matrix of any order
 * 
 * @tparam R Number of rows
 * @tparam C Number of columns
 * @tparam T 
 */
template <size_t R, size_t C, typename T = float>
class mat {
private:
    std::array<std::array<T, C>, R> _mat{};

public:
    mat(const std::array<std::array<T, C>, R> arr) : _mat(arr) {};

    /**
     * @brief Returns and identity matrix
     * 
     * @return mat<R, C, T> 
     */
    static mat<R, C, T> IDENTITY() {
        std::array<std::array<T, C>, R> _mat{};

        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                _mat.at(i).at(j) = (i == j) ? T(1) : T(0);
            }
        }

        return mat<R, C, T>(_mat);
    }

    /**
     * @brief Returns a zero matrix
     * 
     * @return mat<W, H, T> 
     */
    static mat<R, C, T> ZERO() {
        std::array<std::array<T, C>, R> _mat{};

        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                _mat.at(i).at(j) = T(0);
            }
        }

        return mat<R, C, T>(_mat);
    }

    /**
     * @brief Zero indexed access to the underlying array
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    T& operator[](size_t row, size_t col) {
        return _mat.at(row).at(col);
    }

    /**
     * @brief const Zero indexed access to the underlying array
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    const T& operator[](size_t row, size_t col) const {
        return _mat.at(row).at(col);
    }

    /**
     * @brief zero indexed access to 1x3 matrix for each row
     * 
     * @param row 
     * @return mat<1, C, T> 
     */
    mat<1, C, T> operator[](size_t row) {
        mat<1, C, T> res = mat<1, C, T>::ZERO();
        for (size_t i = 0; i < C; i++) {
            res[0, i] = *this[row, i];
        }
        return res;
    }
    
    /**
     * @brief One indexed access to the underlying array
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    T& operator()(size_t row, size_t col) {
        assert(row >= 1 && col >= 1);
        return _mat.at(row - 1).at(col - 1);
    }

    /**
     * @brief addition assignment operator
     * 
     * @param lhs left hand matrix
     * @return mat<R, C, T>& the same matrix but with the lhs added to it
     */
    mat<R, C, T>& operator+=(const mat<R, C, T>& lhs) {
        for(size_t i = 0; i < R; i++) {
            for(size_t j = 0; j < C; j++) {
                (*this)[i, j] += lhs[i, j];
            }
        }
        return *this;
    }

    /**
     * @brief addition operator
     * 
     * @param lhs left hand matrix
     * @param rhs right hand matrix
     * @return mat<R, C, T> 
     */
    friend mat<R, C, T> operator+(mat<R, C, T> lhs, const mat<R, C, T>& rhs) {
        lhs += rhs;
        return lhs;
    }

    /**
     * @brief transposes the given matrix
     * converts rows into columns and vice versa
     * @return mat<C, R, T> 
     */
    mat<C, R, T> transpose() {
        mat<C, R, T> res = mat<C, R, T>::ZERO();

        for(size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                res[j, i] = (*this)[i, j];
            }
        }
        return res;
    }
};


#endif // LIBTEXTO_MATH_MAT_H
