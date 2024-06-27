#ifndef TEXTO_VECTOR2_HPP
#define TEXTO_VECTOR2_HPP


class vector2 {
    public:
        float x, y;

        explicit vector2(float x=0, float y=0);
        vector2(const vector2 & vector);

        vector2 operator+ (const vector2 &v) const;
        vector2 & operator+= (const vector2 &v);
        vector2 operator- (const vector2 &v) const;
        vector2 & operator-= (const vector2 &v);

        float &operator[](int i);
};

#endif //TEXTO_VECTOR2_HPP
