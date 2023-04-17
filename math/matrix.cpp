#include "matrix.hpp"
#include "cassert"
#include <complex>

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
    rows = _matrix.getRows();
    cols = _matrix.getCols();
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &_matrix) {
    if (&_matrix == this) return *this;

    unsigned newRows = _matrix.getRows();
    unsigned newCols = _matrix.getCols();

    matrix.resize(newRows);
    for (unsigned i{0}; i < matrix.size(); i++)
        matrix[i].resize(newCols);

    for (unsigned i{0}; i < newCols; i++){
        for (unsigned j{0}; j < newRows; j++)
            matrix[i][j] = _matrix[i][j];
    }

    rows = newRows;
    cols = newCols;

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

    for (unsigned i{0}; i < _matrix.getRows(); i++)
        for (unsigned j{0}; j < _matrix.getCols(); j++)
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

    for (unsigned i{0}; i < _matrix.getRows(); i++)
        for (unsigned j{0}; j < _matrix.getCols(); j++)
            this->matrix[i][j] -= _matrix(i,j);

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &_matrix) {
    Matrix result(_matrix.getRows(), _matrix.getCols(), 0.0);

    for(unsigned i{0}; i < _matrix.getRows(); i++)
        for(unsigned j{0}; j < _matrix.getCols(); j++)
            for (unsigned k{0}; k < _matrix.getRows(); k++)
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
[[maybe_unused]] std::vector<T> Matrix<T>::diagonalVector() {
    std::vector<T> result(rows, 0.0);

    for (unsigned i=0; i<rows; i++) {
        result[i] = this->mat[i][i];
    }

    return result;
}

template<typename T>
T &Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) {
    return this->matrix[row-1][col-1];
}

template<typename T>
const T &Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) const {
    return this->matrix[row-1][col-1];
}

template<typename T>
unsigned Matrix<T>::getRows() const {
    return this->rows;
}

template<typename T>
unsigned Matrix<T>::getCols() const {
    return this->cols;
}
template<typename T>
Matrix<T> Matrix<T>::lookAt(vector3 &eye, vector3 &target, vector3 &up) {
    vector3 xAxis, yAxis, zAxis;
    zAxis = target - eye;
    zAxis.normalize();
    xAxis = up.cross(zAxis);
    xAxis.normalize();
    yAxis = zAxis.cross(xAxis);

    this = Matrix<float>(this->getRows(), this->getCols(),1.0f);
    this(1,1) = xAxis.x; this(2,1) = xAxis.y; this(3,1) = xAxis.z;
    this(1,2) = yAxis.x; this(2,2) = yAxis.y; this(3,2) = yAxis.z;
    this(1,3) = zAxis.x; this(2,3) = zAxis.y; this(3,3) = zAxis.z;
}
template<typename T>
Matrix<T> Matrix<T>::perspectiveFovRH(
        float fov,
        float aspect,
        float zNear,
        float zFar)
{
        auto yScale = (float)(1.0f / std::tan(fov * 0.5f));
        float q = zFar / (zNear - zFar);

        this(1,1) = yScale / aspect;
        this(2,2) = yScale;
        this(3,3) = q;
        this(3,4) = -1.0f;
        this(4,3) = q * zNear;
}
