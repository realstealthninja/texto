cmake_minimum_required(VERSION 3.25)
project(texto)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)
add_executable(
        texto
        main.cpp
        render.hpp
        render.cpp
        scales.hpp
        3d.cpp
        3d.hpp
        matrix.cpp
        matrix.hpp
)
target_link_libraries(texto ${OpenCV_LIBS})