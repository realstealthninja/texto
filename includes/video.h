#ifndef TEXTO_VIDEO_H
#define TEXTO_VIDEO_H

#include "render.h"

class Video : public Renderer {
    private:
    void render() override;

    public:
    void show();

    Video(const std::string& path, EncodeType type) : Renderer(path, type) {};
    ~Video() = default;
};

#endif