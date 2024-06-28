#include <cmath>

#include "vector4.h"


vector4 vector4::toRotationAxis(vector3 axis, float angle) {
    axis.normalize();
    axis *= std::sin(angle * 0.5f);
   return {
        axis,
        std::cos(angle * 0.5f)
   };
}
vector4 vector4::rotationYawPitchRoll(float yaw, float pitch, float roll) {
    float halfRoll = roll * 0.5f;
    float halfPitch = pitch *0.5f;
    float halfYaw = yaw * 0.5f;

    float sinRoll = std::sin(halfRoll);
    float cosRoll = std::cos(halfRoll);
    float sinPitch = std::sin(halfPitch);
    float cosPitch = std::cos(halfPitch);
    float sinYaw = std::sin(halfYaw);
    float cosYaw = std::sin(halfYaw);


    return {
            (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
            (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
            (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
            (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll)};
}
