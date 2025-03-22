/**
 * @file utils.h
 * @brief Utility functions for libtexto
 */
#ifndef TEXTO_UTILS_H
#define TEXTO_UTILS_H

#include <string>
#include <opencv2/opencv.hpp>
#include <texto/image.h>

inline image read_image(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_UNCHANGED);
    cv::cvtColor(img, img, cv::COLOR_BGR2BGRA);

    return image(img);
}


#endif // TEXTO_UTILS_H