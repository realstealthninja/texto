#pragma once
#ifndef TEXTO_RENDER_HPP

#define TEXTO_RENDER_HPP

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

enum EncodeType {
    GSCALE = 0,
    RGB = 1
};

void renderImage(const char* path, EncodeType encodeType);

void renderVideo(const char* path, EncodeType encodeType);


#endif //TEXTO_RENDER_HPP
