#include <exception>
#include <iostream>
#include <regex>

#include <argparse/argparse.hpp>

#include "image.h"
#include "render.h"
#include "video.h"

std::string menu = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
                   "┃                          ┃\n"
                   "┃         0.Image          ┃\n"
                   "┃         1.Video          ┃\n"
                   "┃         2.3D             ┃\n"
                   "┃                          ┃\n"
                   "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
                   "Input?: ";

std::string encoding = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
                       "┃                          ┃\n"
                       "┃      0. GRAY SCALE       ┃\n"
                       "┃      1. RGB              ┃\n"
                       "┃      2. SHORT GRAY       ┃\n"
                       "┃      3. REVERSE GRAY     ┃\n"
                       "┃                          ┃\n"
                       "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
                       "Input?: ";


std::regex RE_IMAGE("(.*\\.(jpe?g|png|bmp)$)");


int main(int argc, char *argv[]) {

    argparse::ArgumentParser program("Texto");

    program.add_argument("-E", "--encode-type").default_value("gscale");
    program.add_argument("-G", "--Text-ui-mode").implicit_value(true).default_value(false);
    auto &media = program.add_mutually_exclusive_group(true);
    media.add_argument("-V").flag();
    media.add_argument("-I").flag();
    media.add_argument("-D").flag();

    program.add_argument("path");

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    if (!program.get<bool>("-G")) {


        EncodeType encoding_type = GSCALE;
        auto path = program.get("path");
        auto encoding_str = program.get("-E");

        if (encoding_str.compare("rgb") == 0) {
            encoding_type = EncodeType::RGB;
        } else if (encoding_str.compare("rgscale")) {
            encoding_type = EncodeType::REVERSE_GSCALE;
        } else if (encoding_str.compare("sgscale")) {
            encoding_type = EncodeType::SHORT_GSCALE;
        } else {
            encoding_type = EncodeType::GSCALE;
        }

        if (program.get<bool>("-I")) {
            Image image(path, encoding_type);
            image.show();
        } else if (program.get<bool>("-V")) {
            Video video(path, encoding_type);
            video.show();
        } else if (program.get<bool>("-D")) {
            render3D();
        }
        return 0;
    }


    int selection = 0;
    int type;
    std::string path;

    std::cout << menu;
    std::cin >> selection;
    std::cout << "Path?: \n";
    std::cin >> path;
    std::cout << encoding;
    std::cin >> type;


    if (selection == 0) {
        Image image(path, static_cast<EncodeType>(type));
        image.show();
    } else if (selection == 1) {
        Video video(path, static_cast<EncodeType>(type));
        video.show();
    } else if (selection == 2) {
        render3D();
    }

    return 0;
}
