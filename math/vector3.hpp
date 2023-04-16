#ifndef TEXTO_VECTOR3_HPP
#define TEXTO_VECTOR3_HPP


class Vector3 {
public:
    float x, y, z;
    explicit Vector3(float x = 0, float y = 0, float z = 0);
    Vector3(const Vector3 &vector);

    Vector3 operator+(const Vector3 &v) const;
    Vector3 &operator+=(const Vector3 &v);
    Vector3 operator-(const Vector3 &v) const;
    Vector3 &operator-=(const Vector3 &v);

    float &operator[](int i);
};


#endif//TEXTO_VECTOR3_HPP
