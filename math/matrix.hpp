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
    Matrix(unsigned _rows, unsigned _cols, const T& t);
    Matrix(const Matrix<T>& _matrix);
    virtual ~Matrix();

    Matrix<T>& operator= (const Matrix<T>& _matrix);

    Matrix<T> operator+ (const Matrix<T>& _matrix);
    Matrix<T>& operator+= (const Matrix<T>&matrix);
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

    [[nodiscard]] unsigned get_rows() const;
    [[nodiscard]] unsigned get_cols() const;
};

#endif //TEXTO_MATRIX_HPP
