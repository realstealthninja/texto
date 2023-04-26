cmake_minimum_required(VERSION 3.25)
project(texto)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)
add_executable(
        texto
        main.cpp
        main.hpp
        render.hpp
        render.cpp
        scales.hpp
        3d.cpp
        3d.hpp
        math/Matrix.cpp
        math/Matrix.hpp
        math/vector2.cpp
        math/vector2.hpp
        math/vector3.cpp
        math/vector3.hpp
        math/vector4.cpp
        math/vector4.hpp
        rgba.hpp
        scales.cpp)
target_link_libraries(texto ${OpenCV_LIBS})