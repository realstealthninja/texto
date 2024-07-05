#include <string>
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <opencv2/opencv.hpp>

// math lib
#include <matrix.h>
#include <vector3.h>

#include "3d.h"
#include "scales.h"



namespace textoEngine {

    // RENDERER
    renderer::renderer(int width, int height) {
        this->width = width;
        this->height = height;
        this->buffer = std::vector<std::vector<std::string> > {};
    }

    void renderer::clear(color colour) {
        for (int i{0}; i < height; i++) {
            std::vector<std::string> line;
            for (int j{0}; j < width; j++) {
                line.push_back(cv::format(
                        "\033[48;2;%i;%i;%im%c\033[0m",
                        colour.r,
                        colour.g,
                        colour.b,
                        constants::grayscale[colour.a % constants::grayscale.length()])
                );
            }
            buffer.push_back(line);
        }
    }

    void renderer::present() {
        static_cast<void>(system("clear"));
        for (int i{0}; i < height; i++) {
            for (int j{0}; j < width; j++){
                std::cout << buffer.at(i).at(j);
            }
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)1000/60));
    }

    void renderer::putText(int x, int y, color colour) {
        buffer[x][y].assign(cv::format(
                "\033[48;2;%i;%i;%im%c\033[0m",
                colour.r,
                colour.g,
                colour.b,
                constants::grayscale[colour.a % constants::grayscale.length()]));
    }


    void renderer::drawText(vector2 &point) {
        color yellow = {105, 225, 215, 45};
        if (point.x >= 0 && point.y >= 0 && point.x < (float) width && point.y < (float) height) {
            putText(std::floor(point.x), std::floor(point.y), yellow);
        }
    }


    void renderer::render(std::vector<vector3> &meshes) {
        auto projectionMatrix = Matrix(3, 2, 0.0f);

        // convert the null projection matrix into a non square identity matrix
        // to ignore the z coordinate
        //
        //  0   0   0  becomes  1  0  0
        //  0   0   0           0  1  0 
    
        projectionMatrix(1,1) = 1.0f;
        projectionMatrix(2,2) = 1.0f;




        for (const auto& mesh : meshes) {
            Matrix mesh_mat(mesh);
            auto result = projectionMatrix * mesh_mat;
            vector2 result_vec = vector2(result(1,1), result(2,1));
            drawText(result_vec);
        }
    }

}
