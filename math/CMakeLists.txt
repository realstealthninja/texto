
add_library(
    math 
    src/matrix.cpp
    src/vector2.cpp
    src/vector3.cpp
    src/vector4.cpp
)

target_include_directories(math PUBLIC includes/)
