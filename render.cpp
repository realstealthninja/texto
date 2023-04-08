#include "render.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "scales.hpp"

using namespace cv;
using namespace std;


struct winsize w{};

vector<string> convertMatIntoArray(const Mat &material, EncodeType encodeType = GSCALE) {
    vector<string> lines;
    for (int i{0}; i < material.rows; i++) {
        string line;
        for (int j{0}; j < material.cols; j++) {
            int pixel = (int)material.at<uchar>(i,j);
            line += GRAYSCALE[pixel % GRAYSCALE.length()];
        }
        lines.push_back(line);
    }
    return lines;
}


void write(const vector<string>& input) {
    system("clear");
    for(const string& value : input){
        cout << value << "\n";
    }
}

void renderImage(const char* path){
    Mat image = imread(path);

    if (image.empty()){
        cout << "couldn't read image";
        exit(-1);
    }
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    resize(image, image, Size((int) w.ws_col, (int) w.ws_row), INTER_LINEAR);
    cvtColor(image, image, COLOR_BGR2GRAY);
    vector<string> imageChar = convertMatIntoArray(image);
    write(imageChar);
}

void renderVideo(const char* path) {
    Mat frame;
    VideoCapture video(path);

    double fps = video.get(CAP_PROP_FPS);
    double displayRate = 1000/fps;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    while(true) {
        video >> frame;

        if (frame.empty()) break;

        resize(frame, frame, Size((int) w.ws_col, (int)w.ws_row), INTER_LINEAR);
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        vector<string> imageChar = convertMatIntoArray(frame);

        write(imageChar);
        this_thread::sleep_for(chrono::milliseconds((int)displayRate));
    }

    video.release();

}

