#include <cassert>
#include <cmath>

#include "matrix.hpp"
#include "vector4.hpp"


Matrix::Matrix(std::size_t _rows, size_t _cols, float t) {
    matrix.resize(_rows);
    for (std::size_t i{0}; i < matrix.size(); i++) {
        matrix[i].resize(_cols, t);
    }
    rows = _rows;
    cols = _cols;
}


Matrix::Matrix(const Matrix &_matrix) {
    matrix = _matrix.matrix;
    rows = _matrix.getRows();
    cols = _matrix.getCols();
}


Matrix &Matrix::operator=(const Matrix &_matrix) {
    if (&_matrix == this) return *this;

    std::size_t newRows = _matrix.getRows();
    std::size_t newCols = _matrix.getCols();

    matrix.resize(newRows);
    for (std::size_t i{0}; i < matrix.size(); i++)
        matrix[i].resize(newCols);

    for (std::size_t i{0}; i < newCols; i++){
        for (std::size_t j{0}; j < newRows; j++)
            matrix[i][j] = _matrix.matrix[i][j];
    }

    rows = newRows;
    cols = newCols;

    return *this;
}


Matrix Matrix::operator+(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + _matrix(i,j);

    return result;
}


Matrix &Matrix::operator+=(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (std::size_t i{0}; i < _matrix.getRows(); i++)
        for (std::size_t j{0}; j < _matrix.getCols(); j++)
            this->matrix[i][j] += _matrix(i,j);

    return *this;
}


Matrix Matrix::operator-(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - _matrix(i,j);

    return result;
}


Matrix &Matrix::operator-=(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (std::size_t i{0}; i < _matrix.getRows(); i++)
        for (std::size_t j{0}; j < _matrix.getCols(); j++)
            this->matrix[i][j] -= _matrix(i,j);

    return *this;
}


Matrix Matrix::operator*(const Matrix &_matrix) {
    assert(this->getCols() == _matrix.getRows());

    Matrix result(_matrix.getRows(), _matrix.getCols(), 0.0);

    for(std::size_t i{0}; i < _matrix.getRows(); i++)
        for(std::size_t j{0}; j < _matrix.getCols(); j++)
            for (std::size_t k{0}; k < _matrix.getRows(); k++)
                result.matrix[i][j] += this->matrix[i][k] * _matrix.matrix[i][k];

    return result;
}


Matrix &Matrix::operator*=(const Matrix &_matrix) {
    Matrix result = (*this) * _matrix;
    (*this) = result;
    return *this;
}


Matrix Matrix::transpose() {
    Matrix result(rows, cols, 0.0);

    for (std::size_t i=0; i<rows; i++) {
        for (std::size_t j=0; j<cols; j++) {
            result(i,j) = this->matrix[j][i];
        }
    }

    return result;
}


Matrix Matrix::operator+(float num) {
    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + num;
    return result;
}


Matrix Matrix::operator-(float num) {
    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - num;
    return result;
}


Matrix Matrix::operator*(float num) {
    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result.matrix[i][j] = this->matrix.at(i).at(j) * num;
    return result;
}


Matrix Matrix::operator/(float num) {
    Matrix result(rows, cols, 0.0);

    for (std::size_t i{0}; i < rows; i++)
        for (std::size_t j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] / num;
    return result;
}


std::vector<float> Matrix::operator*(const std::vector<float> &vector) {
    std::vector<float> result(vector.size(), 0.0);

    for (std::size_t i=0; i<rows; i++)
        for (std::size_t j=0; j<cols; j++)
            result[i] = this->matrix[i][j] * vector[j];

    return result;
}


[[maybe_unused]] std::vector<float> Matrix::diagonalVector() {
    std::vector<float> result(rows, 0.0);

    for (std::size_t i=0; i < rows; i++) {
        result[i] = this->matrix[i][i];
    }

    return result;
}


float &Matrix::operator()(const std::size_t &row, const std::size_t &col) {
    return this->matrix[row-1][col-1];
}


const float &Matrix::operator()(const std::size_t &row, const std::size_t &col) const {
    return this->matrix[row-1][col-1];
}


std::size_t Matrix::getRows() const {
    return this->rows;
}


std::size_t Matrix::getCols() const {
    return this->cols;
}

Matrix Matrix::identity() {
    Matrix result(4, 4, 0.0f);

    result.matrix.at(0).at(0) = 1.0f;
    result.matrix.at(1).at(1) = 1.0f;
    result.matrix.at(2).at(2) = 1.0f;
    result.matrix.at(3).at(3) = 1.0f;
    return result;
}


Matrix Matrix::lookAt(vector3 &eye, vector3 &target, vector3 &up) {
    vector3 xAxis, yAxis, zAxis;
    zAxis = target - eye;
    xAxis = up.cross(zAxis);
    yAxis = zAxis.cross(xAxis);
    zAxis.normalize();
    xAxis.normalize();
    yAxis.normalize();

    Matrix result = Matrix(xAxis, yAxis, zAxis);
    result.matrix[0][3] = -xAxis.dot(eye);
    result.matrix[1][3] = -yAxis.dot(eye);
    result.matrix[2][3] = -zAxis.dot(eye);
    return result;
}

void Matrix::perspectiveFovLh(
        float fov,
        float aspect,
        float zNear,
        float zFar)
{
        auto yScale = static_cast<float>(1.0f / std::tan(fov * 0.5f));
        float depth = zFar - zNear;

        this->matrix[0][0] = yScale / aspect;
        this->matrix[1][1] = yScale;
        this->matrix[2][2] = -zFar / depth;
        this->matrix[2][3] = 1.0f;
        this->matrix[3][2] = (zFar * zNear) / depth;
}
Matrix Matrix::rotation_pitch(float pitch) {
    Matrix roo = Matrix::identity();
    const float cos = std::cos(pitch);
    const float sin = std::sin(pitch);
    roo.matrix[0][0] = 1.0f;
    roo.matrix[1][1] = cos;
    roo.matrix[1][2] = -sin;
    roo.matrix[2][1] = sin;
    roo.matrix[2][2] = cos;
    roo.matrix[3][3] = 1.0f;
    return roo;
}

Matrix Matrix::rotation_roll(float roll) {
    Matrix roo = Matrix::identity();
    const float cos = std::cos(roll);
    const float sin = std::sin(roll);
    roo.matrix[0][0] = cos;
    roo.matrix[0][1] = sin;
    roo.matrix[1][0] = -sin;
    roo.matrix[1][1] = cos;
    roo.matrix[2][2] = 1.0f;
    roo.matrix[3][3] = 1.0f;
    return roo;
}

Matrix Matrix::rotation_yaw(float yaw) {
    Matrix roo = Matrix::identity();
    const float cos = std::cos(yaw);
    const float sin = std::sin(yaw);
    roo.matrix[0][0] = cos;
    roo.matrix[0][2] = -sin;
    roo.matrix[1][1] = 1.0f;
    roo.matrix[2][0] = sin;
    roo.matrix[2][2] = cos;
    roo.matrix[3][3] = 1.0f;
    return roo;
}

Matrix Matrix::rotationYawPitchRoll(float yaw, float pitch, float roll) {
    Matrix rotated_matrix = Matrix::identity();
    rotated_matrix *= Matrix::rotation_roll(roll);
    rotated_matrix *= Matrix::rotation_pitch(pitch);
    rotated_matrix *= Matrix::rotation_yaw(yaw);
    return rotated_matrix;
}

Matrix Matrix::rotationYawPitchRoll(const vector3& v) {
    return rotationYawPitchRoll(v.y, v.x, v.z);
}

Matrix Matrix::translation(const vector3& v) {
    Matrix result = Matrix::identity();

    result.matrix[3][0] = v.x;
    result.matrix[3][1] = v.y;
    result.matrix[3][2] = v.z;
    return result;
}

Matrix Matrix::scale(const float x, const float y, const float z) {
    Matrix result = Matrix(4, 4, 0.0f);
    result.matrix[0][0] = x;
    result.matrix[1][1] = y;
    result.matrix[2][2] = z;
    result.matrix[3][3] = 1.0f;
    return result;
}
Matrix Matrix::scale(const vector3& v) {
    return Matrix::scale(v.x, v.y, v.z);
}
vector3 Matrix::transformCoordinate(const vector3& v) const {
    auto vector = vector4(1,1,1,1);
    vector.x = (v.x * this->matrix[0][0]) + (v.y * this->matrix[1][0]) + (v.z * this->matrix[2][0]) + this->matrix[3][0];
    vector.y = (v.x * this->matrix[0][1]) + (v.y * this->matrix[1][1]) + (v.z * this->matrix[2][1]) + this->matrix[3][1];
    vector.z = (v.x * this->matrix[0][2]) + (v.y * this->matrix[1][2]) + (v.z * this->matrix[2][2]) + this->matrix[3][2];
    vector.w = 1.0f / (v.x * this->matrix[0][3]) + (v.y * this->matrix[1][3]) + (v.z * this->matrix[2][3]) + this->matrix[3][3];

    return vector3(vector.x * vector.w, vector.y * vector.w, vector.z *  vector.w);
}

Matrix::Matrix(const vector3& top,const vector3& middle,const vector3& bottom) {
    Matrix result(4,4, 0.0f);
    this->rows = result.getRows();
    this->cols = result.getCols();
    this->matrix = result.matrix;
    this->matrix[0] = *new std::vector<float>{top.x, top.y, top.z};
    this->matrix[1] = *new std::vector<float>{middle.x, middle.y, middle.z};
    this->matrix[2] = *new std::vector<float>{bottom.x, bottom.y, bottom.z};
}
