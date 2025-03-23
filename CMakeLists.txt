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

option(BUILD_DOC "Build documentation" ON)

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

# add math dir
add_subdirectory(libtexto-math)
add_subdirectory(libtexto)

if(BUILD_TESTING)
  enable_testing()
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

if(BUILD_DOC)
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
      # install doxygen-awesome
      include(FetchContent)
      FetchContent_Declare(
        doxygen-awesome-css
        URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
      )
      FetchContent_MakeAvailable(doxygen-awesome-css)
      FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)
      
      # set input and output files
      set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

      # request to configure the file
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      message("Doxygen build started")
      
      
      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif()


target_link_libraries(texto ${OpenCV_LIBS} libtexto-math libtexto )
target_compile_options(texto PRIVATE -Wall -Wextra -Wpedantic -Wno-error)
