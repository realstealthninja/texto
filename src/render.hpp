#pragma once
#ifndef TEXTO_RENDER_HPP

#define TEXTO_RENDER_HPP

#include <string>
#include <vector>

enum EncodeType {
    GSCALE = 0,
    RGB = 1,
    SHORT_GSCALE = 2,
    REVERSE_GSCALE = 3
};

void renderImage(const char* path, EncodeType encodeType);

void renderVideo(const char* path, EncodeType encodeType);

[[noreturn]] void render3D();

#endif //TEXTO_RENDER_HPP
