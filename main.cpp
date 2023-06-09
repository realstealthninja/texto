#include "src/main.hpp"
#include "src/render.hpp"
#include <iostream>
#include <regex>

using namespace std;

regex RE_IMAGE("(.*\\.(jpe?g|png|bmp)$)");

int main(int argc, char** argv) {

    EncodeType encodeType = GSCALE;
    if (argc == 3) {
        if (strcmp(argv[2], "GSCALE") != 0)
            encodeType = RGB;

        if (regex_match(argv[1], RE_IMAGE))
            renderImage(argv[1], encodeType);
        else
            renderVideo(argv[1], encodeType);

        return 0;
    }

    int selection;
    int type;
    std::string path;
    cout << menu;
    cin >> selection;
    cout << "Path?: ";
    cin >> path;
    cout << encoding;
    cin >> type;

    switch (selection) {
        case 0:
            renderImage(path.c_str(), (EncodeType) type);
            break;
        case 1:
            renderVideo(path.c_str(), (EncodeType) type);
            break;
        case 2:
            render3D();
        default:
            cout << "please pick either 0 or 1 ";
            break;
    }

    return 0;
}
