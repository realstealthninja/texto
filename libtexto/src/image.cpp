#include <format>
#include <memory>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <texto/image.h>

using namespace texto;

typedef cv::Vec4b Pixel;

const std::string scale = " .'`^\",:;Il!i><~+_-?][}{1)(|/\\tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

void image::resize(int width, int height) {

    cv::resize(
        img,
        img,
        cv::Size(width, height),
        0, 0, cv::INTER_AREA
    );
}

std::shared_ptr<array2d_string> image::to_ascii() {
    std::shared_ptr<array2d_string> res = std::make_shared<array2d_string>(
        this->img.rows,
        std::vector<std::string>(static_cast<size_t>(this->img.cols))
    );
    std::shared_ptr<array2d_string> result = std::make_shared<array2d_string>();
    this->img.forEach<Pixel>(
        [&](const Pixel& pixel, const int position[]) {
            res->at(
                static_cast<size_t>(position[0])
            ).at(
                static_cast<size_t>(position[1])
            ) = std::format(
                "\033[48;2;{};{};{}m\033[38;2;{};{};{}m{}\033[0m",
                pixel[2], pixel[1], pixel[0],
                pixel[2], pixel[1], pixel[0],
                scale.at(pixel[3] % scale.size())
            );
        }
    );
    return res;
}