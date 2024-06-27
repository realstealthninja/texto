#include <opencv2/opencv.hpp>

#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include "image.h"
#include "render.h"

void Image::render() {
    struct winsize w{};

    cv::Mat image = cv::imread(get_path());

    if (image.empty()){
        std::cout << "couldn't read image";
        exit(-1);
    }
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    resize(image, image, cv::Size((int) w.ws_col, (int) w.ws_row), cv::INTER_LINEAR);

    if(get_type() == EncodeType::GSCALE)
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
    set_art(array_to_ascii(image, get_type()));
}
