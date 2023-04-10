#include <iostream>
#include <regex>
#include "render.hpp"

using namespace std;

regex RE_IMAGE("(.*\\.(jpe?g|png|bmp)$)");

int main(int argc, char** argv) {
    EncodeType encodeType = GSCALE;
    if (argc != 3) {
        cout << "Not enough arguments!";
        return -1;
    }
    if (strcmp(argv[2], "GSCALE") != 0)
        encodeType = RGB;
    if (regex_match(argv[1], RE_IMAGE))
        renderImage(argv[1], encodeType);
    else
        renderVideo(argv[1], encodeType);

    return 0;
}
