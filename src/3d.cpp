#include "3d.hpp"
#include "math/Matrix.hpp"
#include "scales.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace textoEngine {
    // CAMERA
    camera::camera(const vector3& position, const vector3& target) {
        this->position = position;
        this->target = target;
    }

    vector3 camera::getPosition() const {
        return position;
    }

    vector3 camera::getTarget() const {
        return target;
    }

    // MESH
    mesh::mesh(std::string name, vector3 position, vector3 rotation, std::vector<vector3> vertices) {
        this->name = std::move(name);
        this->position = position;
        this->rotation = rotation;
        this->vertices = std::move(vertices);
    }
    mesh::mesh(std::string name) : name(std::move(name)) {
        this->position = vector3(0,0,0);
        this->rotation = vector3(0,0,0);
        this->vertices = std::vector<vector3> {};
    }
    // RENDERER
    renderer::renderer(int width, int height) {
        this->width = width;
        this->height = height;
        this->buffer = std::vector<std::vector<std::string> > {};
    }
    void renderer::clear(rgba colour) {
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
        system("clear");
        for (int i{0}; i < height; i++) {
            for (int j{0}; j < width; j++){
                std::cout << buffer.at(i).at(j);
            }
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((int)1000/60));
    }
    void renderer::putText(int x, int y, rgba colour) {
        buffer[x][y] = cv::format(
                "\033[48;2;%i;%i;%im%c\033[0m",
                colour.r,
                colour.g,
                colour.b,
                constants::grayscale[colour.a % constants::grayscale.length()]);
    }
    vector2 renderer::project(const vector3& coordinates, const Matrix& transformationMatrix) const {
        vector3 point = transformationMatrix.transformCoordinate(coordinates);
        float x =  point.x * (float)width + (float) width/4.0f;
        float y  = -point.y * (float)height + (float)height/-4.0f;
        return vector2(x, y);
    }
    void renderer::drawText(vector2 &point) {
        if (point.x >= 0 && point.y >= 0 && point.x < (float) width && point.y < (float) height) {
            putText((int)point.x, (int)point.y, rgba(2, 2, 1, 255));
        }
    }
    void renderer::render(camera &cam, std::vector<mesh> &meshes) {
        Matrix viewMatrix = Matrix(4,4, 0.0f);
        vector3 up(0.0f, 1.0f, 0.0f);
        viewMatrix = viewMatrix.lookAt(cam.position,
                                       cam.target,
                                       up);
        Matrix projectionMatrix = Matrix(4,4,0.0f);
        projectionMatrix.perspectiveFovRh(0.78f, (float) width/(float)height,
                                          0.01f, 1.0f);
        for(const auto& mesh : meshes) {
            Matrix worldMatrix(4,4, 0.0f);
            worldMatrix = worldMatrix.rotationYawPitchRoll(mesh.rotation.y, mesh.rotation.x, mesh.rotation.z) * worldMatrix.translation(mesh.position);
            Matrix transformationMatrix = worldMatrix * viewMatrix;
            for(auto& vertex : mesh.vertices) {
                vector2 point = project(vertex, transformationMatrix);
                drawText(point);
            }
        }
    }

}
