#ifndef TEXTO_VECTOR2_HPP
#define TEXTO_VECTOR2_HPP


class Vector2 {
    public:
        float x,y;

        explicit Vector2(float x=0, float y=0);
        Vector2(const Vector2& vector);

        Vector2 operator+ (const Vector2 &v) const;
        Vector2 & operator+= (const Vector2 &v);
        Vector2 operator- (const Vector2 &v) const;
        Vector2& operator-= (const Vector2 &v);

        float &operator[](int i);
};

#endif //TEXTO_VECTOR2_HPP
