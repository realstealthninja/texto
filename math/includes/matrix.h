#ifndef TEXTO_MATRIX_H
#define TEXTO_MATRIX_H


#include <vector>
#include "vector3.h"

// this implementation of the Matrix was stolen from https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File/

class Matrix {
private:
    std::vector<std::vector<float> > matrix;
    std::size_t rows{};
    std::size_t cols{};
public:
    /**
     * @brief Constructs a new Matrix object
     * 
     * @param _rows number of rows
     * @param _cols number of columns
     * @param t float to be filled
     */
    Matrix(std::size_t _rows, std::size_t _cols, float t);

    /**
     * @brief Constructs a new Matrix from an old Matrix object
     * 
     * @param _matrix 
     */
    Matrix(const Matrix& _matrix);
    /**
     * @brief Construct a new Matrix object from three vector3s
     * 
     * @param top top vector corresponds to (1, 1) (1, 2) (1, 3)
     * @param middle middle vector corresponds to (2, 1) (2, 2) (2, 3)
     * @param bottom 
     */
    Matrix(const vector3& top,const vector3& middle,const vector3& bottom);
    Matrix(const vector3& vec);

    Matrix& operator=  (const Matrix& _matrix);
    Matrix  operator+  (const Matrix& _matrix);
    Matrix& operator+= (const Matrix& matrix);
    Matrix  operator-  (const Matrix& _matrix);
    Matrix& operator-= (const Matrix& _matrix);
    Matrix  operator*  (const Matrix& _matrix);
    Matrix& operator*= (const Matrix& _matrix);
    Matrix transpose();

    Matrix operator+(float num);
    Matrix operator-(float num);
    Matrix operator*(float num);
    Matrix operator/(float num);

    static Matrix identity();

    std::vector<float> operator*(const std::vector<float>& vector);
    [[maybe_unused]] std::vector<float> diagonalVector();

    /**
     * @brief value at (x, y)
     * @note REMEMBER USES (1, 1) to refer to first element [0][0]
     */
    float& operator()(const std::size_t& row, const std::size_t& col);

    /**
     * @brief value at (x, y)
     * 
     * @param row 
     * @param col 
     * @return const float&
     */
    const float& operator()(const std::size_t& row, const std::size_t& col) const;

    /**
     * @brief Gets the number of rows
     * 
     * @return std::size_t 
     */
    [[nodiscard]] std::size_t getRows() const;

    /**
     * @brief Gets the number of columns
     * 
     * @return std::size_t 
     */
    [[nodiscard]] std::size_t getCols() const;


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

#endif //TEXTO_MATRIX_H
