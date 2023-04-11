#ifndef TEXTO_MATRIX_HPP
#define TEXTO_MATRIX_HPP

#include <vector>

// this implementation of the matrix was stolen from https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File/

template <typename T> class Matrix {
private:
    std::vector<std::vector<T> > matrix;
    unsigned rows;
    unsigned cols;
public:
    Matrix(unsigned rows, unsigned cols, const T& t);
    Matrix(const Matrix<T>& _matrix);
    virtual ~Matrix();

    Matrix<T>& operator= (const Matrix<T>& _matrix);

    Matrix<T> operator+ (const Matrix<T>& _matrix);
    Matrix<T>& operator+= (const Matrix<T>& _matrix);
    Matrix<T> operator- (const Matrix<T>& _matrix);
    Matrix<T>& operator-= (const Matrix<T>& _matrix);
    Matrix<T> operator* (const Matrix<T>& _matrix);
    Matrix<T>& operator*= (const Matrix<T>& _matrix);
    Matrix<T> transpose();

    Matrix<T> operator+(const T& num);
    Matrix<T> operator-(const T& num);
    Matrix<T> operator*(const T& num);
    Matrix<T> operator/(const T& num);

    std::vector<T> operator*(const std::vector<T>& vector);
    std::vector<T> diagonal_vector();

    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    unsigned get_rows() const;
    unsigned get_cols() const;
};




#include "matrix.cpp"

#endif //TEXTO_MATRIX_HPP
