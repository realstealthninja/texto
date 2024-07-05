cmake_minimum_required(VERSION 3.25)
project(texto
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "A text based renderer"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(OpenCV REQUIRED)

add_executable(
        texto
        main.cpp
        src/render.cpp
        src/3d.cpp
        src/image.cpp
        src/video.cpp
        src/scales.cpp
)

target_include_directories(texto PRIVATE includes/)

include_directories(".")

# EXTERNAL PACKAGES

# argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)



# add math dir
add_subdirectory(math)

target_link_libraries(texto ${OpenCV_LIBS} math argparse)
target_compile_options(texto PRIVATE -Wall -Wextra -Wpedantic -Wno-error)
