#include <list>
#include <type_traits>
#include <iostream>
#include <complex>
#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

namespace math {
namespace poly {


template <typename T, typename std::enable_if<std::is_arithmetic<T>{}, bool>::type = true>
class Polynomial {
    std::list<std::complex<T>> _coef; 
    // coefficients of an*x^n + an-1*x^n-1 + ... + a1*x + a0
    
    auto get_coef() {
        return _coef;
    }

    const auto get_coef() const{
        return _coef;
    }

  public:
    
    Polynomial(std::list<std::complex<T>> coef) : _coef{coef} {}

    const std::list<std::complex<T>> get_coefs() const {
        return _coef;
    }

    size_t get_size() const {
        return _coef.size();
    }

    size_t get_power() const {
        size_t pow = _coef.size()-1;

        std::complex<T> null(0, 0);
            
        auto it = _coef.begin();
        auto ite = _coef.end();
        for(; (it != ite) && (*it == null); ++it) {
            --pow;
        }

        return pow;
    }

    void pad_to_size(const size_t& size) {
        std::cout << "size = " << size << std::endl;
        if(size < _coef.size()) {
            throw std::logic_error("Trying to pad to size which is lower than the power of the polynomial");
        }
          
        for (int i = size-_coef.size(); i > 0; --i) {
            _coef.emplace_front(0, 0);
        }
    }

    void Dump() {
        std::cout << *this;
    }
  
    Polynomial(std::list<T> coef) {
        for(auto&& x : coef) {
            _coef.emplace_back(x, 0);
        }
    }

    Polynomial<T> operator+(Polynomial<T>& poly) {
        std::list<std::complex<T>> sum_coefs;

        size_t pow = poly.get_power();
        size_t my_pow = get_power();
        
        if(pow > my_pow) {
            pad_to_size(pow + 1); 
        }
        else {
            poly.pad_to_size(my_pow + 1);
        }
        
        std::complex<T> first;
        std::complex<T> second;

        BOOST_FOREACH(boost::tie(first, second), boost::combine(poly._coef, _coef)) {
            sum_coefs.push_back(first + second);
        }

        return Polynomial<T>(sum_coefs);        
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly){
    
    size_t max_pow = poly.get_size();
    size_t curr_pow = max_pow;
    for (auto&& coef : poly.get_coefs()) {
        if(curr_pow != max_pow)
            os << "+ ";
        os << coef << "*x^" << curr_pow-1 << " ";
        --curr_pow;
    }   

    os << std::endl;
    return os;
}

}; // namespace poly
}; // namespace math
