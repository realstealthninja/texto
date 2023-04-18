#ifndef TEXTO_VECTOR4_HPP
#define TEXTO_VECTOR4_HPP


#include "vector3.hpp"
class vector4 {
public:
    float x,y,z,w;
    vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    vector4(vector3 &vec, float w): x(vec.x), y(vec.y), z(vec.z), w(w) {};
    explicit vector4(float n): x(n), y(n), z(n), w(n) {};
    static vector4 toRotationAxis(vector3 axis, float angle);
    vector4 rotationYawPitchRoll(float yaw, float pitch, float roll);
    
};


#endif//TEXTO_VECTOR4_HPP
