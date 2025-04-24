project(
    libtexmath
    LANGUAGES CXX
    VERSION 1.5.0
    DESCRIPTION "The math library used by texto"
)

add_library(libtexmath INTERFACE)

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
    include(CTest)
    include(Catch)
    # test dirs
    add_subdirectory(tests/)
endif()

target_include_directories(libtexmath INTERFACE includes/)

