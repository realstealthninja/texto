#ifndef LIBTEXTO_MATH_VEC_H
#define LIBTEXTO_MATH_VEC_H


#include <cmath>

/**
 * @brief contains math functions and classes 
 */
namespace texmath {

template<typename  T = float>
class vec3 {
public:
    T x{};
    T y{};
    T z{};

    vec3(T x, T y, T z) : x(x), y(y), z(z) {};

    T length_squared() {
        return (x*x + y*y + z*z);
    }

    T length() {
        return std::sqrt(x*x + y*y + z*z);
    }

    vec3<T> operator+=(const vec3<T>& lhs) {
        this->x += lhs.x;
        this->y += lhs.y;
        this->z += lhs.z;

        return *this;
    }

    friend vec3<T> operator+(vec3<T> lhs, const vec3<T>& rhs) {
        lhs += rhs;
        return lhs;
    }

    vec3<T> operator-=(const vec3<T>& lhs) {
        this->x -= lhs.x;
        this->y -= lhs.y;
        this->z -= lhs.z;

        return *this;
    }

    friend vec3<T> operator-(vec3<T> lhs, const vec3<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }

    vec3<T> operator*=(const T scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    friend vec3<T> operator*(vec3<T> lhs, const T scalar) {
        lhs *= scalar;
        return lhs;
    }

    T dot(const vec3<T>& lhs) {
        return this->x * lhs.x + this->y * lhs.y + this->z * lhs.z;
    }

    static T dot(const vec3<T>& lhs, const vec3<T>& rhs) {
        return lhs.dot(rhs);
    }

    vec3<T> cross(const vec3<T>& lhs) {
        return 
        {
            (this->y * lhs.z) - (this->z * lhs.y),
            (this->x * lhs.z) - (this->z * lhs.x),
            (this->x * lhs.y) - (this->y * lhs.x)
        };
    }
    
    static vec3<T> cross(const vec3<T>& lhs, const vec3<T>& rhs) {
        return lhs.cross(rhs);
    }

};

} // texmath

#endif // LIBTEXTO_MATH_VEC_H