#include <iostream>
#include "render.hpp"

using namespace std;

int main(int argc, char ** argv) {
    if (argc != 3) {
        cout << "Not enough arguments!";
        return -1;
    }

    render(argv[1]);

    return 0;
}
