add_executable(
    libtexto-tests
    zeromatrix.cpp
)

target_link_libraries(libtexto-tests PRIVATE  Catch2::Catch2WithMain libtexto-math)
include(Catch)
catch_discover_tests(libtexto-tests)
add_test(NAME libtexto-tests COMMAND libtexto-tests)