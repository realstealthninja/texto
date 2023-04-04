cmake_minimum_required(VERSION 3.25)
project(texto)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)
add_executable(texto render.cpp scales.hpp)
target_link_libraries(texto ${OpenCV_LIBS})