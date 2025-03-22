add_library(
    libtexto
    src/image.cpp
)

target_include_directories(libtexto PUBLIC includes/)
target_link_libraries(libtexto ${OpenCV_LIBS})