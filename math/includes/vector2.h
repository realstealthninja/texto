#ifndef TEXTO_VECTOR2_H
#define TEXTO_VECTOR2_H


#include <ostream>
#include <vector>

class vector2 {
    public:
        float x, y;

        explicit vector2(float x=0, float y=0);
        vector2(const vector2& vector);
        vector2(const std::vector<float>& vec);

        vector2 operator+ (const vector2 &v) const;
        vector2 & operator+= (const vector2 &v);
        vector2 operator- (const vector2 &v) const;
        vector2 & operator-= (const vector2 &v);

        float &operator[](int i);

        friend std::ostream& operator<< (std::ostream& out, const vector2 &vec);
};

#endif //TEXTO_VECTOR2_H
