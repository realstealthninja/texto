#include "vector2.hpp"
#include "cassert"

Vector2::Vector2(float x, float y) : x(x), y(y){};
Vector2::Vector2(const Vector2 &vector) : x(vector.x), y(vector.y) {}

Vector2 Vector2::operator+(const Vector2 &v) const {
    return Vector2(x + v.x, y + v.y);
}

Vector2 &Vector2::operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &v) const {
    return Vector2(x - v.x, y - v.y);
}

Vector2 &Vector2::operator-=(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

float &Vector2::operator[](int i) {
    assert(i == 1 || i == 0);
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
    }
}
