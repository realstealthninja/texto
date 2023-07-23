#ifndef TEXTO_VECTOR3_HPP
#define TEXTO_VECTOR3_HPP

class vector3 {
public:
    float x, y, z;
    explicit vector3(float x = 0, float y = 0, float z = 0);
    vector3(const vector3 &vector);

    vector3 operator+(const vector3 &v) const;
    vector3 &operator+=(const vector3 &v);
    vector3 operator-(const vector3 &v) const;
    vector3 operator-() const;
    vector3 &operator-=(const vector3 &v);
    vector3 &operator*= (const vector3 &v);

    vector3 &operator*= (const float &n);

    float &operator[](int i);

    // other operations
    vector3 cross(vector3 &v) const;
    float dot(vector3 &v) const;
    void normalize();
};

#endif//TEXTO_VECTOR3_HPP
