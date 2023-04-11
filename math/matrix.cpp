#include "cassert"
#include "matrix.hpp"

template<typename T>
Matrix<T>::Matrix(unsigned int _rows, unsigned int _cols, const T &t) {
    matrix.resize(_rows);
    for (unsigned i{0}; i < matrix.size(); i++) {
        matrix[i].resize(_cols, t);
    }
    rows = _rows;
    cols = _cols;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &_matrix) {
    matrix = _matrix.matrix;
    rows = _matrix.get_rows();
    cols = _matrix.get_cols();
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &_matrix) {
    if (&_matrix == this) return *this;

    unsigned new_rows = _matrix.get_rows();
    unsigned new_cols = _matrix.get_cols();

    matrix.resize(new_rows);
    for (unsigned i{0}; i < matrix.size(); i++)
        matrix[i].resize(new_cols);

    for (unsigned i{0}; i < new_cols; i++){
        for (unsigned j{0}; j < new_rows; j++)
            matrix[i][j] = _matrix[i][j];
    }

    rows = new_rows;
    cols = new_cols;

    return *this;
}

template<typename T>
Matrix<T>::~Matrix() = default;

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + _matrix(i,j);

    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (unsigned i{0}; i < _matrix.get_rows(); i++)
        for (unsigned j{0}; j < _matrix.get_cols(); j++)
            this->matrix[i][j] += _matrix(i,j);

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - _matrix(i,j);

    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (unsigned i{0}; i < _matrix.get_rows(); i++)
        for (unsigned j{0}; j < _matrix.get_cols(); j++)
            this->matrix[i][j] -= _matrix(i,j);

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &_matrix) {
    Matrix result(_matrix.get_rows(), _matrix.get_cols(), 0.0);

    for(unsigned i{0}; i < _matrix.get_rows(); i++)
        for(unsigned j{0}; j < _matrix.get_cols(); j++)
            for (unsigned k{0}; k < _matrix.get_rows(); k++)
                result(i,j) += this->mat[i][k] * _matrix(k,j);

    return result;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &_matrix) {
    Matrix result = (*this) * _matrix;
    (*this) = result;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix result(rows, cols, 0.0);

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[j][i];
        }
    }

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T &num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + num;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T &num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - num;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] * num;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T &num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] / num;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T> &vector) {
    std::vector<T> result(vector.size(), 0.0);

    for (unsigned i=0; i<rows; i++)
        for (unsigned j=0; j<cols; j++)
            result[i] = this->mat[i][j] * vector[j];

    return result;
}

template<typename T>
std::vector<T> Matrix<T>::diagonal_vector() {
    std::vector<T> result(rows, 0.0);

    for (unsigned i=0; i<rows; i++) {
        result[i] = this->mat[i][i];
    }

    return result;
}

template<typename T>
T &Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) {
    return this->matrix[row][col];
}

template<typename T>
const T &Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) const {
    return this->matrix[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
    return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const {
    return this->cols;
}





