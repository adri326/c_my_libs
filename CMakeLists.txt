cmake_minimum_required(VERSION 3.12)

project(TEST)
enable_testing()
add_test(NAME my_libs_test COMMAND my_libs_test)

add_executable(my_libs_test test/main.c)

include(include.cmake)

target_link_libraries(my_libs_test my_libs m)
