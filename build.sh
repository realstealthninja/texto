if [ ! -d "build" ]; then
    mkdir build
fi

cd build &&
cmake .. &&
cmake --build ./ --target texto -j 8 
