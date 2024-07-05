#ifndef TEXTO_3D_H
#define TEXTO_3D_H

#include <string>

#include <matrix.h>
#include <vector2.h>
#include <vector3.h>
#include "rgba.h"

namespace textoEngine {

    class renderer {
    private:
        std::vector<std::vector<std::string> > buffer;

    public:

        int width; ///< width of screen
        int height; ///< height of screen
        renderer(int width, int height);
        void present();
        void putText(int x, int y , color color);
        void drawText(vector2 &point);
        void clear(color color);
        void render(std::vector<vector3> &meshes);
    };
}

#endif //TEXTO_3D_H
