cmake_minimum_required(VERSION 3.28)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost)

SET(CXX_STANDARD C++23 REQUIRED)
project(fft_poly)

add_subdirectory(src)
add_subdirectory(apps)


