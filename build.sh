if [ ! -d "build" ]; then
    mkdir build
fi

cd build

if [ "$1" = "test" ]; then
    cmake .. -DBUILD_TESTING=TRUE
else
    cmake ..
fi 

cmake --build ./ -j $(nproc)
