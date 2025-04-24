add_executable(
    texto-tests
    zeromatrix.cpp
    transpose.cpp
    addition.cpp
    substraction.cpp
    multiplication.cpp
    access.cpp
)

if(ENABLE_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
        set(LINK_OPTIONS "${LINK_OPTIONS} --coverage")
    else()
        message("Code coverage not yet supported for this compiler")
    endif()

endif()

include(Catch)
target_link_libraries(texto-tests PRIVATE Catch2::Catch2WithMain libtexmath)
catch_discover_tests(texto-tests)

option(ENABLE_COVERAGE "Build with gcov coverage." OFF)