#include "render.hpp"
#include "scales.hpp"
#include "3d.hpp"
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#include <vector>

using namespace cv;
using namespace std;


struct winsize w{};

vector<string> convertMatIntoArray(Mat &material, EncodeType encodeType = GSCALE) {
    vector<string> lines;
    Mat colors[3];
    std::string scale;

    switch (encodeType){
        case GSCALE:
            scale = constants::grayscale;
            break;
        case RGB:
            split(material, colors);
            cvtColor(material, material, COLOR_BGR2GRAY);
            scale = constants::grayscale;
            break;
        case SHORT_GSCALE:
            scale = constants::shortGrayscale;
            break;
        case REVERSE_GSCALE:
            scale = constants::reversedGrayscale;
    }

    for (int i{0}; i < material.rows; i++) {
        string line;
        for (int j{0}; j < material.cols; j++) {
            int pixel = (int)material.at<uchar>(i,j);
            if (encodeType != GSCALE){
                // [38 for foreground and 48 for background
                // shouts out to Leonhard Euler for doing math
                line += cv::format(
                        "\033[48;2;%i;%i;%im%c\033[0m",
                        (int)colors[2].at<uchar>(i,j),
                        (int)colors[1].at<uchar>(i,j),
                        (int)colors[0].at<uchar>(i,j),
                        constants::grayscale[pixel % constants::grayscale.length()]);
            } else {
                line += scale[pixel % scale.length()];
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



    while(true) {
        video >> frame;

        if (frame.empty()) break;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        resize(frame, frame, Size((int) w.ws_col, (int)w.ws_row), INTER_LINEAR);
        if(encodeType == GSCALE)
            cvtColor(frame, frame, COLOR_BGR2GRAY);

        vector<string> imageChar = convertMatIntoArray(frame, encodeType);

        write(imageChar);
        this_thread::sleep_for(chrono::milliseconds((int)displayRate));
    }

    video.release();
}

void render3D() {

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    textoEngine::renderer renderer(w.ws_col, w.ws_row);
    textoEngine::camera cam(
            vector3(0,0,10.0f),
            vector3(0,0,0)
    );
    textoEngine::mesh mesh("cube");
    mesh.vertices.emplace_back(-1,1,1);
    mesh.vertices.emplace_back(1,1,1);
    mesh.vertices.emplace_back(-1,-1,1);
    mesh.vertices.emplace_back(-1,-1,-1);
    mesh.vertices.emplace_back(-1,1,-1);
    mesh.vertices.emplace_back(1,1,-1);
    mesh.vertices.emplace_back(1,-1,1);
    mesh.vertices.emplace_back(1,-1,-1);
    std::vector<textoEngine::mesh> meshes;
    meshes.push_back(mesh);
    renderer.clear(rgba(0,0,0,0));
    while(true) {
        renderer.height = w.ws_row;
        renderer.width = w.ws_col;
        renderer.render(cam, meshes);
        renderer.present();
    }
}
