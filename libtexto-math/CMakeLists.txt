add_library(
    libtexto-math 
    src/mat.cpp
    src/matrix.cpp
    src/vector2.cpp
    src/vector3.cpp
    src/vector4.cpp
)

target_include_directories(libtexto-math PUBLIC includes/)

