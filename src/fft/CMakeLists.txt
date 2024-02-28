set(TARGET fft_lib)

add_library(${TARGET} fft.cpp)

target_compile_features(${TARGET} PUBLIC cxx_std_23)

target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/headers)

target_link_libraries(${TARGET} PUBLIC ${Boost_LIBRARIES})
