#ifndef TEXTO_IMAGE_H
#define TEXTO_IMAGE_H

#include <memory>
#include <opencv4/opencv2/core.hpp>
#include <vector>
#include <string>

typedef std::vector<std::vector<std::string> >  array2d_string;

class image {
public:
    image(cv::Mat img) : img(img) {};

    void resize(int width, int height);
    std::shared_ptr<array2d_string> to_ascii();
    
private:
    cv::Mat img;
};

#endif // TEXTO_IMAGE_H