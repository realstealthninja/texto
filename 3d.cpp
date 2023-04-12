#include <string>
#include <utility>
#include <vector>
#include "3d.hpp"

namespace textoEngine {

    // CAMERA
    Camera::Camera(vector3 position, vector3 target) {
        Position = position;
        Target = target;
    }

    vector3 Camera::getPosition() const {
        return Position;
    }

    vector3 Camera::getTarget() const {
        return Target;
    }

    // MESH
    Mesh::Mesh(std::string name, vector3 position, vector3 rotation, std::vector<vector3> vertices) {
        Name = std::move(name);
        Position = position;
        Rotation = rotation;
        Vertices = std::move(vertices);
    }
}