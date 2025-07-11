#ifndef LIBTEXTO_MATH_MAT_H
#define LIBTEXTO_MATH_MAT_H

#include <array>
#include <cassert>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <ostream>
#include <stdexcept>

/**
 * @brief contains math functions and classes 
 */
namespace texmath {

/**
 * @brief A templated matrix class able to represent a matrix of any order
 * 
 * \f[
 *  A  = \begin{bmatrix} a_{11} & a_{12} & a_{13} & \dots & a_{1n} \\
 *                       a_{21} & a_{22} & a_{23} & \dots & a_{2n} \\ 
 *                       a_{31} & a_{32} & a_{33} & \dots & a_{3n} \\
 *                       \vdots & \vdots & \vdots & \ddots& \vdots \\
 *                       a_{n1} & a_{n2} & a_{n3} & \dots & a_{nn}
 *      \end{bmatrix}
 * \f]
 * 
 * @tparam R Number of rows
 * @tparam C Number of columns
 * @tparam T type of the members of the matrix
 */
template <size_t R, size_t C, typename T = float>
class mat {
private:
    std::array<std::array<T, C>, R> _mat{};

public:
    /**
     * @brief Constructs a new mat object
     * 
     * @param arr an array of the same order as the desired matrix
     */
    mat(const std::array<std::array<T, C>, R> arr) : _mat(arr) {};

    mat(const std::initializer_list<std::initializer_list<T> > arr) {
        if(arr.size() != R || (*arr.begin()).size() != C) {
            throw std::invalid_argument(
                std::format(
                    "Array{}x{} is not the same size as matrix{}x{}",
                    arr.size(), (*arr.begin()).size(),
                    R,C
                )
            );
        }

        for(size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C; j++) {
                _mat.at(i).at(j) = *((*(arr.begin() + i)).begin() + j);
            }
        }
    }

    /**
     * @brief Returns an identity matrix
     * \f[
     *  I_{3\times3} = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}_{3\times3}  
     * \f]
     * @return mat<R, C, T> an identity matrix of order RxC
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
        if(row > R || col > C) {
            throw std::invalid_argument("Specified index out of bounds");
        }

        return _mat.at(row).at(col);
    }

    /**
     * @brief const Zero indexed access to the underlying array
     *
     *  \f[ A = \begin{bmatrix} 1 & 2 & 3\\a & b & c \end{bmatrix} \f]
     *  @code{.cpp}
     *  mat<3,3> A({1, 2, 3}, {a, b, c});
     *  A[0, 0]; // is 1 
     *  @endcode
     * 
     * @param row the row to be accessed
     * @param col the col to be accessed
     * @return T& 
     */
    const T& operator[](size_t row, size_t col) const {
        if(row > R || col > C) {
            throw std::invalid_argument("Specified index out of bounds");
        }
        return _mat.at(row).at(col);
    }

    /**
     * @brief zero indexed access to \f$1xC\f$ matrix for each row
     * 
     * @param row 
     * @return mat<1, C, T> 
     */
    mat<1, C, T> operator[](size_t row) {
        if(row > R) {
            throw std::invalid_argument("Specified index out of bounds");
        }

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
        if(row < 1 || col < 1 || row > R || col > C) {
            throw std::invalid_argument("Specified index out of bounds");
        }
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
     * @brief substraction assignment operator
     * 
     * @param lhs right hand matrix
     * @return mat<R, C, T>& the resultant matrix
     */
    mat<R, C, T>& operator-=(const mat<R, C, T>& lhs) {
        for(size_t i = 0; i < R; i++) {
            for(size_t j = 0; j < C; j++) {
                (*this)[i, j] -= lhs[i, j];
            }
        }
        return *this;
    }

    /**
     * @brief substraction operator
     * 
     * @param lhs left hand matrix
     * @param rhs right hand matrix
     * @return mat<R, C, T> the resultant matrix
     */
    friend mat<R, C, T> operator-(mat<R, C, T> lhs, const mat<R, C, T>& rhs) {
        lhs -= rhs;
        return lhs;
    }

    /**
     * @brief mutliplies and assigns a scalar to a matrix
     * 
     * @param scalar the scalar to be multiplied
     * @return mat<R, C, T>& the resultant matrix
     */
    mat<R, C, T>& operator*=(const T scalar) {
        for(size_t i = 0; i < R; i++) {
            for(size_t j = 0; j < C; j++) {
                (*this)[i, j] *= scalar;
            }
        }
        return *this;
    }

    /**
     * @brief multiplies a scalar with a matrix
     * 
     * @param lhs left hand matrix
     * @param scalar scalar quantity
     * @return mat<R, C, T> the resultant matrix
     */
    friend mat<R, C, T> operator*(mat<R, C, T> lhs, const T scalar) {
        lhs *= scalar;
        return lhs;
    }
    
    /**
     * @brief divides and assigns a scalar to a matrix
     * 
     * @param scalar the scalar to be divded
     * @return mat<R, C, T>& the resultant matrix
     */
    mat<R, C, T>& operator/=(const T scalar) {

        for(size_t i = 0; i < R; i++) {
            for(size_t j = 0; j < C; j++) {
                (*this)[i, j] /= scalar;
            }
        }
        return *this;
    }

    /**
     * @brief divdes a scalar with a matrix
     * 
     * @param lhs left hand matrix
     * @param scalar scalar quantity
     * @return mat<R, C, T> the resultant matrix
     */
    friend mat<R, C, T> operator/(mat<R, C, T> lhs, const T scalar) {
        lhs /= scalar;
        return lhs;
    }

    /**
     * @brief multilpies two matrices
     * 
     * @tparam C2 no of columns of the second matrix
     * @param lhs left hand matrix
     * @param rhs right hand matrix
     * @return mat<R, C2, T> the multiplied matrix
     */
    template<size_t C2>
    friend mat<R, C2, T> operator*(mat<R, C, T> lhs, const mat<C, C2, T>& rhs) {

        mat<R, C2, T> _mat = mat<R, C2, T>::ZERO();

        for (size_t i = 0; i < R; i++) {
            for (size_t j = 0; j < C2; j++) {
                for (size_t k = 0; k < C; k++) {
                    _mat[i, j] += lhs[i, k] * rhs[k, j];
                }
            }
        }
        return _mat;
    }

    /**
     * @brief compares two matrices
     * 
     * @param lhs left hand matrix
     * @param rhs right hand matrix
     * @return true if the matrices are equal
     * @return false if the matrices are not equal
     */
    friend bool operator==(const mat<R, C, T> lhs, const mat<R, C, T>& rhs) {
        for(size_t i = 0; i < R; i++) {
            for(size_t j = 0; j < C; j++) {
                if (lhs[i, j] != rhs[i, j]) {
                    return false;
                }
            }
        }
        return true;
    }


    /**
     * @brief transposes the given matrix
     * converts rows into columns and vice versa
     * 
     *  \f{eqnarray*}{
     *      A &=& \begin{bmatrix} 1 & 2 & 3\\a & b & c \end{bmatrix}\\ \\
     *      A^\intercal &=& \begin{bmatrix} 1 & 2 & 3\\a & b & c \end{bmatrix}^\intercal \\ \\ 
     *        &=& \begin{bmatrix} 1 & a \\ 2 & b \\ 3 & c \end{bmatrix} 
     *   \f}
     * @return mat<C, R, T> The transposed matrix of order CxR
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

    /**
     * @brief checks if the matrix is a square matrix
     * 
     * @return `true` if the matrix is square
     * @return `false` if the matrix is not square
     */
    bool is_square() {
        return C == R;
    }
};

/**
 * @brief Insertion operator overload for a matrix
 * 
 * @tparam R no of rows of the matrix
 * @tparam C no of columns of the matrix
 * @tparam T type of the elements of the matrix
 * @param os outstream
 * @param obj the matrix object
 * @return std::ostream& the modified outstream
 */
template <size_t R, size_t C, typename T = float>
std::ostream& operator<<(std::ostream& os, const mat<R, C, T>& obj) {

    os << std::format("┌{}┐\n", std::string((C*2) + 3 , ' '));
    for (size_t i = 0; i < R; i++) {
        std::string row = "";
        for (size_t j = 0; j < C; j++) {
            row += std::format("{} ", obj[i, j]);
        }
        os << std::format("│  {} │\n", row);
    }
    os << std::format("└{}┘\n", std::string((C*2) + 3 , ' '));
    return os;
}

} // texmath

#endif // LIBTEXTO_MATH_MAT_H
