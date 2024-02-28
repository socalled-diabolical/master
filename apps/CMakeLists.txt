set(TARGET conv_poly)

add_executable(${TARGET} conv_poly.cpp)

target_compile_features(${TARGET} PUBLIC cxx_std_23)

target_link_libraries(${TARGET} PRIVATE fft_lib)


