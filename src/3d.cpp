#include <cstddef>
#include <cstdlib>
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
        buffer.resize(height);
        for (int i{0}; i < height; i++) {
            buffer[i].resize(width);
            for(int j{0}; j < width; j++) {
                buffer[i][j] = " ";
            }
        }
    }

    void renderer::clear(color colour) {
        static_cast<void>(system("clear"));
        
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
            buffer[i] = line;
        }
    }

    void renderer::present() {
        for (std::size_t i{0}; i < buffer.size(); i++) {
            for (std::size_t j{0}; j < buffer[i].size(); j++){
                std::cout << buffer.at(i).at(j);
            }
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void renderer::putText(int x, int y, color colour) {
        this->buffer.at(x).at(y).assign( 
            std::format(
                "\033[48;2;{};{};{}m{}\033[0m",
                colour.r, 
                colour.g,
                colour.b,
                constants::grayscale[colour.a % constants::grayscale.length()]));
    }


    void renderer::drawText(vector2 &point) {
        color yellow = {255, 0, 0, 2};
        if (point.x >= 0 && point.y >= 0 && point.x < (float) width && point.y < (float) height) {
            putText(std::floor(point.x), std::floor(point.y), yellow);
            
        } else {
            std::cout << std::format("out of range x: {} y:{} width:{} height:{}\n", point.x, point.y, width, height);
        }
    }


    void renderer::render(std::vector<vector3> &meshes) {
        auto projectionMatrix = Matrix(2, 3, 0.0f);

        // convert the null projection matrix into a non square identity matrix
        // to ignore the z coordinate
        //
        //  0   0   0  becomes  1  0  0
        //  0   0   0           0  1  0 


        //  multiply given coordinate matrix by projection matrix
        //   1   0   0      x   0   0       x   0   0
        //   0   1   0  *   0   y   0   =   0   y   0
        //                  0   0   z  
        
    
        projectionMatrix(1,1) = 1.0f;
        projectionMatrix(2,2) = 1.0f;


        for (const auto& mesh : meshes) {
            auto object_matrix = Matrix(3, 3, 0.0f);

            object_matrix(1, 1) = mesh.x;
            object_matrix(2, 2) = mesh.y;
            object_matrix(3, 3) = mesh.z;

            auto resultant_matrix = projectionMatrix * object_matrix;

            // convert result matrix to vector 2;

            auto resultant_vector = vector2(object_matrix.diagonalVector());
            resultant_vector.x =  (((resultant_vector.x + 1)* 0.5) * (width-1));
            resultant_vector.y += std::abs((1-((resultant_vector.y +1) * 0.5)) * (height-1));
            //std::clog << resultant_vector << std::endl;

            drawText(resultant_vector);
        }
    }

}
