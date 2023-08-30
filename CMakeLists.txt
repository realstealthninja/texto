cmake_minimum_required(VERSION 3.25)
project(texto
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "A text based renderer (soon to be game engine)"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(OpenCV REQUIRED)
add_executable(
        texto
        main.cpp
        src/main.hpp
        src/render.hpp
        src/render.cpp
        src/scales.hpp
        src/3d.cpp
        src/3d.hpp
        src/math/Matrix.cpp
        src/math/Matrix.hpp
        src/math/vector2.cpp
        src/math/vector2.hpp
        src/math/vector3.cpp
        src/math/vector3.hpp
        src/math/vector4.cpp
        src/math/vector4.hpp
        src/rgba.hpp
        src/scales.cpp
)

target_link_libraries(texto ${OpenCV_LIBS})
target_compile_options(texto PRIVATE -Wall -Wextra -Wpedantic -Werror)
