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
        math/matrix.cpp
        math/matrix.hpp
        math/vector2.cpp math/vector2.hpp math/vector3.cpp math/vector3.hpp)
target_link_libraries(texto ${OpenCV_LIBS})