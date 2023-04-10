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

vector<string> convertMatIntoArray(Mat &material, EncodeType encodeType = GSCALE) {
    vector<string> lines;
    Mat colors[3];
    if (encodeType != GSCALE) {
        split(material, colors);
        cvtColor(material, material, COLOR_BGR2GRAY);
    }
    for (int i{0}; i < material.rows; i++) {
        string line;
        for (int j{0}; j < material.cols; j++) {
            int pixel = (int)material.at<uchar>(i,j);
            if (encodeType != GSCALE){
                // [38 for foreground and 48 for background
                // shouts out to Leonhard Euler for doing math
                line += format(
                        "\033[48;2;%i;%i;%im%c\033[0m",
                        (int)colors[2].at<uchar>(i,j),
                        (int)colors[1].at<uchar>(i,j),
                        (int)colors[0].at<uchar>(i,j),
                        GRAYSCALE[pixel % GRAYSCALE.length()]);
            } else {
                line += GRAYSCALE[pixel % GRAYSCALE.length()];
            }
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

void renderImage(const char* path, EncodeType encodeType = GSCALE){
    Mat image = imread(path);

    if (image.empty()){
        cout << "couldn't read image";
        exit(-1);
    }
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    resize(image, image, Size((int) w.ws_col, (int) w.ws_row), INTER_LINEAR);

    if(encodeType == GSCALE)
        cvtColor(image, image, COLOR_BGR2GRAY);
    vector<string> imageChar = convertMatIntoArray(image, encodeType);
    write(imageChar);
}

void renderVideo(const char* path, EncodeType encodeType = GSCALE) {
    Mat frame;
    VideoCapture video(path);

    double fps = video.get(CAP_PROP_FPS);
    double displayRate = 1000/fps;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    while(true) {
        video >> frame;

        if (frame.empty()) break;

        resize(frame, frame, Size((int) w.ws_col, (int)w.ws_row), INTER_LINEAR);
        if(encodeType == GSCALE)
            cvtColor(frame, frame, COLOR_BGR2GRAY);

        vector<string> imageChar = convertMatIntoArray(frame, encodeType);

        write(imageChar);
        this_thread::sleep_for(chrono::milliseconds((int)displayRate));
    }

    video.release();

}

