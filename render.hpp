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

void render(const char * path);

#endif //TEXTO_RENDER_HPP
