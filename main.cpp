#include <iostream>
#include "render.hpp"
#include "main.hpp"

using namespace std;

int main() {
    int selection;
    int type;
    std::string path;
    cout << MENU;
    cin >> selection;
    cout << "Path?: ";
    cin >> path;
    cout << ENCODING;
    cin >> type;

    switch(selection) {
        case 0:
            renderImage(path.c_str(), (EncodeType) type);
            break;
        case 1:
            renderVideo(path.c_str(), (EncodeType) type);
            break;
        default:
            cout << "please pick either 0 or 1 ";
            break;
    }

    return 0;
}
