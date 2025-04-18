#include "texto/utils.h"
#include <iostream>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <texto/image.h>
#include <texmath/mat.h>
#include <texto/utils.h>
#include <sys/ioctl.h>

using namespace texto;

int main() {
    
    image im = read_image("../examples/euler.jpg");
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    im.resize(w.ws_col, w.ws_row);
    std::shared_ptr<array2d_string> str = im.to_ascii();
    for (const auto& ele : *(str.get())) {
        for (const auto& ele2 : ele) {
            std::cout << ele2;
        }
        std::cout << "\n";
    }
    return 0;
}
