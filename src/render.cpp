
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#include <vector>

#include <vector2.hpp>
#include <vector4.hpp>

#include "render.h"
#include "scales.hpp"
#include "3d.hpp"

void Renderer::output() {
    system("clear");
    for (const std::string& line : art) {
        std::cout << line << "\n";
    }
}
void Renderer::show() {
    render();
    output();
}

EncodeType Renderer::get_type() {
    return this->type;
}

std::string& Renderer::get_path() {
    return this->path;
}

void Renderer::set_art(std::vector<std::string> arr) {
    this-> art = arr;
}

std::vector<std::string> Renderer::get_art() {
    return this-> art;
}

void Renderer::set_type(EncodeType type) {
    this->type = type;
}

Renderer::~Renderer() = default;

struct winsize w{};

std::vector<std::string> array_to_ascii(cv::Mat& material, EncodeType encodeType) {
    std::vector<std::string> lines;
    cv::Mat colors[3];
    std::string scale;

    switch (encodeType){
        case GSCALE:
            scale = constants::grayscale;
            break;
        case RGB:
            cv::split(material, colors);
            cv::cvtColor(material, material, cv::COLOR_BGR2GRAY);
            scale = constants::grayscale;
            break;
        case SHORT_GSCALE:
            scale = constants::shortGrayscale;
            break;
        case REVERSE_GSCALE:
            scale = constants::reversedGrayscale;
    }

    for (int i{0}; i < material.rows; i++) {
        std::string line;
        for (int j{0}; j < material.cols; j++) {
            int pixel = (int)material.at<uchar>(i,j);
            if (encodeType == RGB){
                int red = static_cast<int> (colors[2].at<uchar>(i,j));
                int green = static_cast<int> (colors[1].at<uchar>(i,j));
                int blue = static_cast<int> (colors[0].at<uchar>(i,j));
                // [38 for foreground and 48 for background
                // shouts out to Leonhard Euler for doing math
                line += cv::format(
                        "\033[48;2;%i;%i;%im\033[38;2;%i;%i;%im%c\033[0m",
                        red,green, blue, // background
                        red, green, blue, // foreground
                        scale[pixel % scale.length()]);
            } else {
                line += scale[pixel % scale.length()];
            }
        }
        lines.push_back(line);
    }
    return lines;
}


void write(const std::vector<std::string>& input) {
    system("clear");
    for(const std::string& value : input){
        std::cout << value << "\n";
    }
}

void render_video(const char* path, EncodeType encodeType = EncodeType::GSCALE) {
    cv::Mat frame;
    cv::VideoCapture video(path);

    double fps = video.get(cv::CAP_PROP_FPS);
    double displayRate = 1000/fps;



    while(true) {
        video >> frame;

        if (frame.empty()) break;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        resize(frame, frame, cv::Size((int) w.ws_col, (int)w.ws_row), cv::INTER_LINEAR);
        if(encodeType == GSCALE)
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        std::vector<std::string> imageChar = array_to_ascii(frame, encodeType);

        write(imageChar);
        std::this_thread::sleep_for(std::chrono::milliseconds((int)displayRate));
    }

    video.release();
}

void render_3d() {

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    textoEngine::renderer renderer(w.ws_col, w.ws_row);
    textoEngine::camera cam(
            vector3(0,0,10.0f),
            vector3(0,0,0)
    );
    
    textoEngine::mesh mesh("cube");
    
    mesh.vertices.emplace_back(-1,  1,  1);
    mesh.vertices.emplace_back( 1,  1,  1);
    mesh.vertices.emplace_back(-1, -1,  1);
    mesh.vertices.emplace_back(-1, -1, -1);
    mesh.vertices.emplace_back(-1,  1, -1);
    mesh.vertices.emplace_back( 1,  1, -1);
    mesh.vertices.emplace_back( 1, -1,  1);
    mesh.vertices.emplace_back( 1, -1, -1);

    mesh.scale = vector3(1,1,1);
    mesh.position = vector3(0,0,0);
    
    std::vector<textoEngine::mesh> meshes;
    meshes.push_back(mesh);

    struct color black = {0, 0, 0, 0};
    renderer.clear(black);
    while(true) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        renderer.height = w.ws_row;
        renderer.width = w.ws_col;
#ifndef NDEBUG
        renderer.height = 80;
        renderer.width = 120;
#endif
        struct color white = {255, 255, 255, 255};
        renderer.clear(white);
        renderer.render(cam, meshes);
        renderer.present();
        mesh.rotation = vector3(mesh.rotation.x + 0.01f, mesh.rotation.y, mesh.rotation.z);
    }
}
