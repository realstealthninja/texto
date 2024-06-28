#ifndef TEXTO_3D_H
#define TEXTO_3D_H

#include <string>

#include <matrix.h>
#include <vector2.h>
#include <vector3.h>
#include "rgba.h"

namespace textoEngine {
    class camera {
        public:
            vector3 position{};
            vector3 target{};
            camera(const vector3& position, const vector3& target);
            [[nodiscard]] vector3 getPosition() const;
            [[nodiscard]] vector3 getTarget() const;
    };


    class mesh {
        public:
            std::string name;
            vector3 position{};
            vector3 rotation{};
            vector3 scale{};
            std::vector<vector3> vertices;
            mesh(
                    std::string name,
                    const vector3& position,
                    vector3 rotation,
                    std::vector<vector3> vertices
            );
            explicit mesh(std::string name);
    };
    class renderer {
    public:
        std::vector<std::vector<std::string> > buffer;
        int width; ///< width of screen
        int height; ///< height of screen
        /**
         * @brief constructor of renderer
         * @param width of screen
         * @param height of screen
         */
        renderer(int width, int height);
        void clear(color color);
        void present();
        void putText(int x, int y , color color);
        [[nodiscard]] vector2 project(const vector3& coordinates, const Matrix& transformationMatrix) const;
        void drawText(vector2 &point);
        void render(camera &cam, std::vector<mesh> &meshes);
    };
}

#endif //TEXTO_3D_H
