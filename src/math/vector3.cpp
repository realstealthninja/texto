#include "vector3.hpp"
#include <cassert>
#include <cmath>

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
        default:
            return x;
    }
}
vector3 vector3::cross(vector3 &v) const {
    return vector3(
            (y * v.z) - (z *v.y),
            (z * v.x) - (x * v.z),
            (x * v.y) - (y * v.x)
    );
}
vector3 &vector3::operator*=(const float &n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}
void vector3::normalize() {
    float length = std::sqrt((x*x) + (y*y) + (z*z));
    if (length != 0){
        float inverse = 1.0f / length;
        *this *= inverse;
    }
}
