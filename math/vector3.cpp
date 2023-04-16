#include "vector3.hpp"
#include "Vector4.hpp"
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
Vector3 Vector3::TransformCoordinate(Vector3 &coordinate, Matrix<float> &transform) {
    Vector4 vector = Vector4();
    vector.x = (coordinate.x * transform(1,1)) + (coordinate.y * transform(2,1)) + (coordinate.z * transform(3,1)) + transform(4,1);
    vector.y = (coordinate.x * transform(1,2)) + (coordinate.y * transform(2,2)) + (coordinate.z * transform(3,2)) + transform(4,2);
    vector.z = (coordinate.x * transform(1,3)) + (coordinate.y * transform(2,3)) + (coordinate.z * transform(3,3)) + transform(4,3);
    vector.w = 1.0f / (coordinate.x * transform(1,4)) + (coordinate.y * transform(2,4)) + (coordinate.z * transform(3,4)) + transform(4,4);

    return Vector3(vector.x * vector.w, vector.y * vector.w, vector.z * vector.w);
}
