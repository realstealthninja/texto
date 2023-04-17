#include "vector2.hpp"
#include "cassert"

vector2::vector2(float x, float y) : x(x), y(y){};
vector2::vector2(const vector2 &vector) : x(vector.x), y(vector.y) {}

vector2 vector2::operator+(const vector2 &v) const {
    return vector2(x + v.x, y + v.y);
}

vector2 &vector2::operator+=(const vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

vector2 vector2::operator-(const vector2 &v) const {
    return vector2(x - v.x, y - v.y);
}

vector2 &vector2::operator-=(const vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

float &vector2::operator[](int i) {
    assert(i == 1 || i == 0);
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
    }
}
