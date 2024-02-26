set(TARGET fft_lib)

add_library(${TARGET} fft.cpp)

target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/headers)
