#include "vector3.hpp"
#include "vector4.hpp"
#include <cassert>
#include <math.h>

vector3::vector3(float x, float y, float z) : x(x), y(y), z(z) {}
vector3::vector3(const vector3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
}
vector3 vector3::operator+(const vector3 &v) const {
    return vector3(x + v.x, y + v.y, z + v.z);
}
vector3 &vector3::operator+=(const vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
vector3 vector3::operator-(const vector3 &v) const {
    return vector3(x-v.x, y-v.y, z-v.z);
}
vector3 &vector3::operator-=(const vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
vector3 &vector3::operator*=(const vector3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}
float &vector3::operator[](int i) {
    assert(i == 2 || i == 1 || i == 0);
    switch(i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;

    }
}
vector3 vector3::TransformCoordinate(vector3 &coordinate, Matrix<float> &transform) {
    auto vector = vector4(1);
    vector.x = (coordinate.x * transform(1,1)) + (coordinate.y * transform(2,1)) + (coordinate.z * transform(3,1)) + transform(4,1);
    vector.y = (coordinate.x * transform(1,2)) + (coordinate.y * transform(2,2)) + (coordinate.z * transform(3,2)) + transform(4,2);
    vector.z = (coordinate.x * transform(1,3)) + (coordinate.y * transform(2,3)) + (coordinate.z * transform(3,3)) + transform(4,3);
    vector.w = 1.0f / (coordinate.x * transform(1,4)) + (coordinate.y * transform(2,4)) + (coordinate.z * transform(3,4)) + transform(4,4);

    return vector3(vector.x * vector.w, vector.y * vector.w, vector.z * vector.w);
}
vector3 vector3::cross(vector3 &v) const {
    return vector3(
            (y * v.z) - (z *v.y),
            (z * v.x) - (x * v.z),
            (x * v.y) - (y * v.x)
    );
}
void vector3::normalize() {
    float length = std::sqrt((x*x) + (y*y) + (z*z));
    if (length != 0){
        float inverse = 1.0f / length;
        x *= inverse;
        y *= inverse;
        z *= inverse;
    }
}
vector3 &vector3::operator*=(const float &n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}
