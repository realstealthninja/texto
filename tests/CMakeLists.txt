add_executable(
    texto-tests
    zeromatrix.cpp
    transpose.cpp
    addition.cpp
    multiplication.cpp
)


include(Catch)
target_link_libraries(texto-tests PRIVATE Catch2::Catch2WithMain libtexmath)
catch_discover_tests(texto-tests)