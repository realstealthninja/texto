#ifndef TEXTO_IMAGE_H 
#define TEXTO_IMAGE_H

#include "render.h"


class Image : public Renderer {
    private:
    void render() override;

    public:
    Image(const std::string& path, EncodeType type) : Renderer(path, type) {};

    ~Image() = default;
};

#endif // TEXTO_IMAGE_H