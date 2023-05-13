#pragma  once
#ifndef TEXTO_3D_HPP
#define TEXTO_3D_HPP


#include "math/Matrix.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "rgba.hpp"
#include <string>

namespace textoEngine {
    class camera {
        public:
            vector3 position{};
            vector3 target{};
            camera(vector3 position, vector3 target);
            [[nodiscard]] vector3 getPosition() const;
            [[nodiscard]] vector3 getTarget() const;
    };


    class mesh {
        public:
            std::string name;
            vector3 position{};
            vector3 rotation{};
            std::vector<vector3> vertices;
            mesh(
                    std::string name,
                    vector3 position,
                    vector3 rotation,
                    std::vector<vector3> vertices
            );
            explicit mesh(std::string name);
    };
    class renderer {
    public:
        std::vector<std::vector<std::string> > buffer;
        int width;
        int height;
        renderer(int width, int height);
        void clear(rgba color);
        void present();
        void putText(int x, int y , rgba colour);
        [[nodiscard]] vector2 project(const vector3& coordinates, const Matrix& transformationMatrix) const;
        void drawText(vector2 &point);
        void render(camera &cam, std::vector<mesh> &meshes);
    };
}

#endif //TEXTO_3D_HPP
