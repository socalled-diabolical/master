#include <vector>
#include <type_traits>
#include <iostream>
#include <complex>

namespace math {
namespace poly {


template <typename T, typename std::enable_if<std::is_arithmetic<T>{}, bool>::type = true>
class Polynomial {
    std::vector<std::complex<T>> _coef; 
    // coefficients of an*x^n + an-1*x^n-1 + ... + a1*x + a0

  public:
    
    Polynomial(std::vector<std::complex<T>> coef) : _coef{coef} {}

    const std::vector<std::complex<T>> get_coefs() const {
        return _coef;
    }

    size_t get_power() const {
        return _coef.size()-1;
    }

    void Dump() {
        std::cout << *this;
    }
  
    Polynomial(std::vector<T> coef) {
        for(auto&& x : coef) {
            _coef.emplace_back(x, 0);
        }
    } 
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly){
    
    size_t max_pow = poly.get_power();
    size_t curr_pow = max_pow;
    for (auto&& coef : poly.get_coefs()) {
        if(curr_pow != max_pow)
            os << "+ ";
        os << coef << "*x^" << curr_pow << " ";
        --curr_pow;
    }   

    os << std::endl;
    return os;
}

}; // namespace poly
}; // namespace math
