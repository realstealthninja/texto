project(
    libtexmath
    LANGUAGES CXX
    VERSION 1.5.0
    DESCRIPTION "The math library used by texto"
)

add_library(libtexmath INTERFACE)

target_include_directories(libtexmath INTERFACE includes/)

