#ifndef TEXTO_VECTOR4_H
#define TEXTO_VECTOR4_H


#include "vector3.h"

class vector4 {
public:
    float x,y,z,w;
    vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    vector4(vector3 &vec, float w): x(vec.x), y(vec.y), z(vec.z), w(w) {};
    explicit vector4(float n): x(n), y(n), z(n), w(n) {};
    static vector4 toRotationAxis(vector3 axis, float angle);
    vector4 rotationYawPitchRoll(float yaw, float pitch, float roll);
};


#endif//TEXTO_VECTOR4_H
