#include <iostream>
#include <regex>
#include "render.hpp"

using namespace std;

regex RE_IMAGE("(.*\\.(jpe?g|png|bmp)$)");

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Not enough arguments!";
        return -1;
    }

    if (regex_match(argv[1], RE_IMAGE))
        renderImage(argv[1]);
    else
        renderVideo(argv[1]);

    return 0;
}
