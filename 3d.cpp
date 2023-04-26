#include "3d.hpp"
#include "scales.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <utility>
#include <vector>
#include "math/Matrix.hpp"

namespace textoEngine {
    // CAMERA
    camera::camera(vector3 position, vector3 target) {
        position = position;
        target = target;
    }

    vector3 camera::getPosition() const {
        return position;
    }

    vector3 camera::getTarget() const {
        return target;
    }

    // MESH
    mesh::mesh(std::string name, vector3 position, vector3 rotation, std::vector<vector3> vertices) {
        name = std::move(name);
        position = position;
        rotation = rotation;
        vertices = std::move(vertices);
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
        buffer = std::vector<std::vector<std::string> >();
    }
    void renderer::clear(rgba colour) {
        for (int i; i < height; i++) {
            for (int j; j < width; j++) {
                buffer[i][j] = cv::format(
                        "\033[48;2;%i;%i;%im%c\033[0m",
                        colour.r,
                        colour.g,
                        colour.b,
                        constants::grayscale[colour.a % constants::grayscale.length()]);
            }
        }
    }
    void renderer::present() {
        for (int i ; i < height; i++) {
            for (int j; j< width; j++){
                std::cout << buffer[i][j] + "\n";
            }
        }
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
        float x =  point.x * (float)width + (float) width/2.0f;
        float y  = -point.y * (float)height + (float)height/2.0f;
        return vector2(x,y);
    }
    void renderer::drawText(vector2 &point) {
        if (point.x >= 0 && point.y >= 0 && point.x <(float) width && point.y < (float) height) {
            putText((int)point.x, (int)point.y, rgba(1, 1, 1, 1));
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
