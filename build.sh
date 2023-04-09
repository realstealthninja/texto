cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -S ./ -B ./cmake-build-release &&
cmake --build ./cmake-build-release --target texto -j 1