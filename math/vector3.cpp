#include "vector3.hpp"
#include <cassert>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3::Vector3(const Vector3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
}
Vector3 Vector3::operator+(const Vector3 &v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 &Vector3::operator+=(const Vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
Vector3 Vector3::operator-(const Vector3 &v) const {
    return Vector3(x-v.x, y-v.y, z-v.z);
}
Vector3 &Vector3::operator-=(const Vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
float &Vector3::operator[](int i) {
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
