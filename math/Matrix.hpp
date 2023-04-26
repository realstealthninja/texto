#ifndef TEXTO_MATRIX_HPP
#define TEXTO_MATRIX_HPP

#include "vector3.hpp"
#include "vector4.hpp"
#include <vector>

// this implementation of the Matrix was stolen from https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File/

class Matrix {
private:
    std::vector<std::vector<float> > matrix;
    unsigned rows;
    unsigned cols;
public:
    Matrix(unsigned _rows, unsigned _cols, float t);
    Matrix(const Matrix& _matrix);

    Matrix& operator= (const Matrix& _matrix);

    Matrix operator+ (const Matrix& _matrix);
    Matrix& operator+= (const Matrix&matrix);
    Matrix operator- (const Matrix& _matrix);
    Matrix& operator-= (const Matrix& _matrix);
    Matrix operator* (const Matrix& _matrix);
    Matrix& operator*= (const Matrix& _matrix);
    Matrix transpose();

    Matrix operator+(float num);
    Matrix operator-(float num);
    Matrix operator*(float num);
    Matrix operator/(float num);

    std::vector<float> operator*(const std::vector<float>& vector);
    [[maybe_unused]] std::vector<float> diagonalVector();

    float& operator()(const unsigned& row, const unsigned& col);
    const float& operator()(const unsigned& row, const unsigned& col) const;

    [[nodiscard]] unsigned getRows() const;
    [[nodiscard]] unsigned getCols() const;

    Matrix lookAt(vector3 &eye, vector3 &target, vector3 &up) const;
    void perspectiveFovRh(float fov, float aspect, float zNear, float zFar);
    Matrix rotationYawPitchRoll(float yaw, float pitch, float roll);
    Matrix translation(vector3 v);
    Matrix rotationQuaternion(vector4 quaternion);
    [[nodiscard]] vector3 transformCoordinate(const vector3& v) const;
};

#endif //TEXTO_MATRIX_HPP
