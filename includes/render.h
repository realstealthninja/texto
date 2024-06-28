#ifndef TEXTO_RENDER_H
#define TEXTO_RENDER_H

#include <opencv2/core.hpp>
#include <string>
#include <vector>

#include <vector2.h>
#include <vector4.h>


enum EncodeType {
    GSCALE = 0,
    RGB = 1,
    SHORT_GSCALE = 2,
    REVERSE_GSCALE = 3
};

void renderImage(const char* path, EncodeType encodeType);

void renderVideo(const char* path, EncodeType encodeType);

std::vector<std::string> array_to_ascii(cv::Mat& material, EncodeType encodeType = EncodeType::GSCALE);

[[noreturn]] void render3D();


class Renderer {
    private:
    std::string path{};
    EncodeType  type{};
    
    std::vector<std::string> art;

    virtual void render() = 0;

    
    public:
    void output();
    void show();

    EncodeType get_type();
    std::string& get_path();
    void set_art(std::vector<std::string> arr);
    void set_type(EncodeType type);
    std::vector<std::string> get_art();

    Renderer(const std::string& path, EncodeType type) : path(path), type(type) {};
    ~Renderer();
};


#endif //TEXTO_RENDER_H
