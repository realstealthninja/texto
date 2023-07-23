#ifndef TEXTO_MATRIX_HPP
#define TEXTO_MATRIX_HPP

#include "vector3.hpp"
#include "vector4.hpp"
#include <vector>

// this implementation of the Matrix was stolen from https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File/

class Matrix {
private:
    std::vector<std::vector<float> > matrix;
    unsigned rows{};
    unsigned cols{};
public:
    Matrix(unsigned _rows, unsigned _cols, float t);
    Matrix(const Matrix& _matrix);
    Matrix(const vector3& top,const vector3& middle,const vector3& bottom);

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

    static Matrix identity();

    std::vector<float> operator*(const std::vector<float>& vector);
    [[maybe_unused]] std::vector<float> diagonalVector();

    float& operator()(const unsigned& row, const unsigned& col);
    const float& operator()(const unsigned& row, const unsigned& col) const;

    [[nodiscard]] unsigned getRows() const;
    [[nodiscard]] unsigned getCols() const;

    static Matrix lookAt(vector3 &eye, vector3 &target, vector3 &up) ;
    void perspectiveFovLh(float fov, float aspect, float zNear, float zFar);
    static Matrix rotation_yaw(float yaw);
    static Matrix rotation_pitch(float pitch);
    static Matrix rotation_roll(float roll);
    static Matrix rotationYawPitchRoll(float yaw, float pitch, float roll);
    static Matrix rotationYawPitchRoll(const vector3& v);
    static Matrix translation(const vector3& v);
    static Matrix scale(float x, float y, float z);
    static Matrix scale(const vector3& v);
    [[nodiscard]] vector3 transformCoordinate(const vector3& v) const;
};

#endif //TEXTO_MATRIX_HPP
