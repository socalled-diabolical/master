set(TARGET conv_poly)

add_executable(${TARGET} conv_poly.cpp)

target_link_libraries(${TARGET} PRIVATE fft_lib)


