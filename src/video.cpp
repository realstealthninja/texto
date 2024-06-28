
#include "render.h"
#include <thread>
#include <opencv2/opencv.hpp>

#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include "video.h"

void Video::render() {
    struct winsize w{};
    cv::Mat frame;
    cv::VideoCapture video(get_path());

    double fps = video.get(cv::CAP_PROP_FPS);
    double display_rate = 1000/fps;




    while(true) {
        video >> frame;

        if (frame.empty()) {
            break;
        }

        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        
        cv::resize(frame, frame, cv::Size((int) w.ws_col, (int)w.ws_row), cv::INTER_LINEAR);
        
        if(get_type() == GSCALE) {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }

        set_art(array_to_ascii(frame, get_type()));
        output();
        
        std::this_thread::sleep_for(std::chrono::milliseconds((int)display_rate));
    }

    video.release();
}

void Video::show() {
    render();
}