#include "Matrix.hpp"
#include "vector4.hpp"
#include <cassert>
#include <complex>


Matrix::Matrix(unsigned int _rows, unsigned int _cols, float t) {
    matrix.resize(_rows);
    for (unsigned i{0}; i < matrix.size(); i++) {
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

    unsigned newRows = _matrix.getRows();
    unsigned newCols = _matrix.getCols();

    matrix.resize(newRows);
    for (unsigned i{0}; i < matrix.size(); i++)
        matrix[i].resize(newCols);

    for (unsigned i{0}; i < newCols; i++){
        for (unsigned j{0}; j < newRows; j++)
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

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + _matrix(i,j);

    return result;
}


Matrix &Matrix::operator+=(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (unsigned i{0}; i < _matrix.getRows(); i++)
        for (unsigned j{0}; j < _matrix.getCols(); j++)
            this->matrix[i][j] += _matrix(i,j);

    return *this;
}


Matrix Matrix::operator-(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - _matrix(i,j);

    return result;
}


Matrix &Matrix::operator-=(const Matrix &_matrix) {
    assert(_matrix.cols == cols);
    assert(_matrix.rows == rows);

    for (unsigned i{0}; i < _matrix.getRows(); i++)
        for (unsigned j{0}; j < _matrix.getCols(); j++)
            this->matrix[i][j] -= _matrix(i,j);

    return *this;
}


Matrix Matrix::operator*(const Matrix &_matrix) {
    Matrix result(_matrix.getRows(), _matrix.getCols(), 0.0);

    for(unsigned i{0}; i < _matrix.getRows(); i++)
        for(unsigned j{0}; j < _matrix.getCols(); j++)
            for (unsigned k{0}; k < _matrix.getRows(); k++)
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

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->matrix[j][i];
        }
    }

    return result;
}


Matrix Matrix::operator+(float num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] + num;
    return result;
}


Matrix Matrix::operator-(float num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] - num;
    return result;
}


Matrix Matrix::operator*(float num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result.matrix[i][j] = this->matrix.at(i).at(j) * num;
    return result;
}


Matrix Matrix::operator/(float num) {
    Matrix result(rows, cols, 0.0);

    for (unsigned i{0}; i < rows; i++)
        for (unsigned j{0}; j < cols; j++)
            result(i,j) = this->matrix[i][j] / num;
    return result;
}


std::vector<float> Matrix::operator*(const std::vector<float> &vector) {
    std::vector<float> result(vector.size(), 0.0);

    for (unsigned i=0; i<rows; i++)
        for (unsigned j=0; j<cols; j++)
            result[i] = this->matrix[i][j] * vector[j];

    return result;
}


[[maybe_unused]] std::vector<float> Matrix::diagonalVector() {
    std::vector<float> result(rows, 0.0);

    for (unsigned i=0; i<rows; i++) {
        result[i] = this->matrix[i][i];
    }

    return result;
}


float &Matrix::operator()(const unsigned int &row, const unsigned int &col) {
    return this->matrix[row-1][col-1];
}


const float &Matrix::operator()(const unsigned int &row, const unsigned int &col) const {
    return this->matrix[row-1][col-1];
}


unsigned Matrix::getRows() const {
    return this->rows;
}


unsigned Matrix::getCols() const {
    return this->cols;
}

Matrix Matrix::lookAt(vector3 &eye, vector3 &target, vector3 &up) const {
    vector3 xAxis, yAxis, zAxis;
    zAxis = target - eye;
    zAxis.normalize();
    xAxis = up.cross(zAxis);
    xAxis.normalize();
    yAxis = zAxis.cross(xAxis);

    Matrix result = Matrix(this->getRows(), this->getCols(), 0.0f);
    result(2,2) = 1.0f;
    result(3,3) = 1.0f;
    result(4,4) = 1.0f;
    result(1,1) = xAxis.x; result(2,1) = xAxis.y; result(3,1) = xAxis.z;
    result(1,2) = yAxis.x; result(2,2) = yAxis.y; result(3,2) = yAxis.z;
    result(1,3) = zAxis.x; result(2,3) = zAxis.y; result(3,3) = zAxis.z;
    return result;
}

void Matrix::perspectiveFovRh(
        float fov,
        float aspect,
        float zNear,
        float zFar)
{
        auto yScale = (float)(1.0f / std::tan(fov * 0.5f));
        float q = zFar / (zNear - zFar);

        this->matrix[0][0] = yScale / aspect;
        this->matrix[1][1] = yScale;
        this->matrix[2][2] = q;
        this->matrix[2][3] = -1.0f;
        this->matrix[3][2] = q * zNear;
}


Matrix Matrix::rotationQuaternion(vector4 quaternion) {
    Matrix result(4,4, 0.0);
    
    float xx = quaternion.x * quaternion.x;
    float yy = quaternion.y * quaternion.y;
    float zz = quaternion.z * quaternion.z;
    float xy = quaternion.x * quaternion.y;
    float zw = quaternion.z * quaternion.w;
    float zx = quaternion.z * quaternion.x;
    float yw = quaternion.y * quaternion.w;
    float yz = quaternion.y * quaternion.z;
    float xw = quaternion.x * quaternion.w;

    result(1,1) = 1.0f - (2.0f * yy);
    result(1,2) = 2.0f * (xy + zw);
    result(1,3) = 2.0f * (zx - yw);
    result(2,1) = 2.0f * (xy - zw);
    result(2,2) = 1.0f - (2.0f * (zz + xx));
    result(2,3) = 2.0f * (yz + xw);
    result(3,1) = 2.0f * (zx + yw);
    result(3,2) = 2.0f * (yz - xw);
    result(3,3) = 1.0f - (2.0f * (yy +xx));
    result(4,4) = 1.0;
    return result;
}


Matrix Matrix::rotationYawPitchRoll(float yaw, float pitch, float roll) {
    vector4 quaternion(0.0);
    quaternion = quaternion.rotationYawPitchRoll(yaw, pitch, roll);
    Matrix result(4,4, 0.0f);
    result = rotationQuaternion(quaternion);
    return result;
}

Matrix Matrix::translation(vector3 v) {
    Matrix result(4,4, 0.0);
    result(1,1) = 1.0f;
    result(2,2) = 1.0f;
    result(3,3) = 1.0f;
    result(4,4) = 1.0f;

    result(4,1) = v.x;
    result(4,2) = v.y;
    result(4,3) = v.z;
    return result;
}
vector3 Matrix::transformCoordinate(const vector3& v) const {
    auto vector = vector4(1,1,1,1);
    vector.x = (v.x * this->matrix[0][0]) + (v.y * this->matrix[1][0]) + (v.z * this->matrix[2][0]) + this->matrix[3][0];
    vector.y = (v.x * this->matrix[0][1]) + (v.y * this->matrix[1][1]) + (v.z * this->matrix[2][1]) + this->matrix[3][1];
    vector.z = (v.x * this->matrix[0][2]) + (v.y * this->matrix[1][2]) + (v.z * this->matrix[2][2]) + this->matrix[3][2];
    vector.w = 1.0f / (v.x * this->matrix[0][3]) + (v.y * this->matrix[1][3]) + (v.z * this->matrix[2][3]) + this->matrix[3][3];

    return vector3(vector.x * vector.w, vector.y * vector.w, vector.z * vector.w);
}
