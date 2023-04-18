#include "vector4.hpp"
#include <complex>

vector4 vector4::toRotationAxis(vector3 axis, float angle) {
    axis.normalize();
    axis *= std::sin(angle * 0.5f);
   return {
        axis,
        std::cos(angle * 0.5f)
   };
}

