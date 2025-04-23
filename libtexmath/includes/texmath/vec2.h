#ifndef LIBTEXMATH_VEC2_H
#define LIBTEXMATH_VEC2_H

#include <cmath>


namespace texmath {

template<typename  T = float>
class vec2 { 
public:
    T x{};
    T y{};

    vec2(T x, T y) : x(x), y(y) {};

    T length_squared() {
        return (x*x + y*y);
    }

    T length() {
        return std::sqrt( x*x + y*y );
    }

    vec2<T> operator+=(const vec2<T>& lhs) {
        this->x += lhs.x;
        this->y += lhs.y;

        return *this;
    }

    friend vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs) {
        lhs += rhs;
        return lhs;
    }

    vec2<T> operator-=(const vec2<T>& lhs) {
        this->x -= lhs.x;
        this->y -= lhs.y;

        return *this;
    }

    friend vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }

    T dot(const vec2<T>& lhs) {
        return this->x * lhs.x + this->y * lhs.y;
    }

    static T dot(const vec2<T>& lhs, const vec2<T>& rhs) {
        return lhs.dot(rhs);
    }


};

}

#endif // LIBTEXMATH_VEC2_H