#include <vector>
#include <ranges>
#include <complex>
#include <iterator>
#include <cmath>
#include <iostream>

namespace math {
namespace fft {

template <typename T>
std::complex<T> complex_exponent_to_sin_cos(const T& angle) {
    return std::complex<T>(std::cos(angle), std::sin(angle));    
}

class FFTInternals {

  private:   
    
    std::vector <std::complex> exponents;
    
  public: 

    FFTInternals(const auto& len) {
        auto base = complex_exponent_to_sin_cos(2*std::pi / len);
        auto multiple = 1;

        for(size_t i = 0; i < len; ++i) {
            exponents.push_back(multiple);
            multiple *= base;
            std::cout << multiple << std::endl;
        }
    }

    auto run(const std::ranges::input_range auto& seq) {
         auto even_index = [index=0](auto val) mutable {
            if(index % 2 == 0 || index == 0) {
                ++index;
                return true;
            }
            ++index;
            return false;
        };

        auto evens = seq | std::views::filter(even_index);
        auto odds = seq | std::views::drop(1) | std::views::filter(even_index);

        fft(evens);
        fft(odds);       
    }
};

void fft(const std::ranges::input_range auto& seq) {
    
    FFTInternals _internals(std::distance(seq.begin(), seq.end()));

//    _internals.run(seq);
}

} // namespace fft
} // namespace math
