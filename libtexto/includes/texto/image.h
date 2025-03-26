#ifndef TEXTO_IMAGE_H
#define TEXTO_IMAGE_H

#include <memory>
#include <opencv4/opencv2/core.hpp>
#include <vector>
#include <string>

/**
 * @brief contains functions and classes related to texto
 * 
 */
namespace texto {

typedef std::vector<std::vector<std::string> >  array2d_string;

/**
 * @brief a wrapper class of cv::Mat
 * 
 */
class image {
private:
    cv::Mat img; ///< opencv image
public:
    /**
     * @brief Construct a new image object from cv::mat
     * 
     * @param img the opencv image to construct an object from
     */
    image(cv::Mat img) : img(img) {};

    /**
     * @brief resizes the image to the given width and height
     * 
     * @param width new width
     * @param height new height
     */
    void resize(int width, int height);

    /**
     * @brief converts the image to ascii
     * 
     * @return std::shared_ptr<array2d_string> 
     */
    std::shared_ptr<array2d_string> to_ascii();
    

};

} // texto

#endif // TEXTO_IMAGE_H