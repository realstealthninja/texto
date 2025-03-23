add_executable(
    libtexto-tests
    zeromatrix.cpp
    transpose.cpp
    addition.cpp
)


include(Catch)
target_link_libraries(libtexto-tests PRIVATE Catch2::Catch2WithMain libtexto-math)
catch_discover_tests(libtexto-tests)