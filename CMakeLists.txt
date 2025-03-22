cmake_minimum_required(VERSION 3.25)
project(texto
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "A text based renderer"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-Wall -Wextra -Wpedantic
                    -Wconversion -Wcast-align
                    -Wunused -Wold-style-cast
                    -Wpointer-arith -Wcast-qual 
                    -Wno-missing-braces)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
        texto
        main.cpp
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
add_subdirectory(libtexto-math)
add_subdirectory(libtexto)

if(BUILD_TESTING)
    # Catch2
    include(FetchContent)

    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.4.0 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    # test dirs
    add_subdirectory(tests/)

    include(CTest)
    include(Catch)

endif()


target_link_libraries(texto ${OpenCV_LIBS} libtexto-math libtexto argparse)
target_compile_options(texto PRIVATE -Wall -Wextra -Wpedantic -Wno-error)
