#include <iostream>
#include <regex>
#include <cstring>

#include "image.h"
#include "render.h"
#include "video.h"

std::string menu = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n" 
                   "┃                          ┃\n"
                   "┃         0.Image          ┃\n"
                   "┃         1.Video          ┃\n"
                   "┃         3.3D             ┃\n"
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

int main(int argc, char** argv) {

    EncodeType encodeType = GSCALE;
    if (argc == 3) {
        if (strcmp(argv[2], "GSCALE") != 0)
            encodeType = RGB;

        if (regex_match(argv[1], RE_IMAGE)) {
            Image image(argv[1], encodeType);
            image.show();
        } else {
           Video video(argv[1], encodeType);
        }
        return 0;
    }

    int selection = 0;
    int type;
    std::string path;
    std::cout << menu;
    std::cin >> selection;
    std::cout << "Path?: ";
    std::cin >> path;
    std::cout << encoding;
    std::cin >> type;
    

    if (selection == 0) {
        Image image(path, static_cast<EncodeType>(type));
        image.show();
    } else if (selection == 1) {
        Video video(path, static_cast<EncodeType>(type));
        video.show();
    }

    return 0;
}
