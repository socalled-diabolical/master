#include <list>
#include <type_traits>
#include <iostream>
#include <complex>
#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>
#include <cmath>

namespace math {
namespace poly {

template <typename T>
class Polynomial {
    std::vector<T> _coef; 
    // coefficients of an*x^n + an-1*x^n-1 + ... + a1*x + a0 from a0 to an 
  public:

    std::vector<T> get_coef() {
        return _coef;
    }

    const std::vector<T> get_coef() const{
        return _coef;
    }

    const std::vector<T> get_coefs() const {
        return _coef;
    }

    size_t get_size() const {
        return _coef.size();
    }

    size_t get_power() const {
        size_t pow = _coef.size()-1;
            
        T null = 0;
        
        auto it = _coef.begin();
        auto ite = _coef.end();
        for(; (it != ite) && (*it == null); ++it) {
            --pow;
        }

        return pow;
    }

    void pad_to_size(const size_t& size) {
        if(size < _coef.size()) {
            throw std::logic_error("Trying to pad to size which is lower than the power of the polynomial");
        }
          
        for (int i = size-_coef.size(); i > 0; --i) {
            _coef.emplace_back(0);
        }
    }

    void Dump() {
        std::cout << *this;
    }
  
    Polynomial(std::vector<T> coef) {
        for(auto&& x : coef) {
            _coef.push_back(x);
        }
    }

    Polynomial(const T& constant) {
        _coef.push_back(constant);
    }

    T operator()(const T& point) {
        T sum = 0;
        auto max_pow = get_power();
        
        auto it = _coef.begin();
        auto ite = _coef.end();

        T point_powered (1.0);
        size_t power = 0; 
        
        for(; it != ite, power <= max_pow; ++it) {
            sum += (*it)*point_powered;
            ++power;
            point_powered *= point;
        }

        return sum;
    }

};

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& lhs, const Polynomial<T>& rhs) {
    std::vector<T> sum_coefs;

    size_t rhs_size = rhs.get_size();
    size_t size = lhs.get_size(); 

    size_t lower_size = (rhs_size > size) ? size : rhs_size;        

    auto coefs1 = lhs.get_coef();
    auto coefs2 = rhs.get_coef();

    for (size_t i = 0; i < lower_size; ++i) {
        sum_coefs.push_back(coefs1[i] + coefs2[i]);
    }

    if(rhs_size == lower_size) {
        for(size_t i = 0; i < size - lower_size; ++i) {
            sum_coefs.push_back(coefs1[i + lower_size]);
        }
    }
    else {
         for(size_t i = 0; i < size - lower_size; ++i) {
            sum_coefs.push_back(coefs2[i + lower_size]);
        }       
    }

    return Polynomial<T>(sum_coefs);        
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly) {
    size_t max_pow = poly.get_size();
    size_t curr_pow = max_pow-1;

    auto coefs = poly.get_coefs();
    auto rbegin = coefs.rbegin();
    auto rit = rbegin;
    auto rite = coefs.rend();

    for (; rit != rite; ++rit) {
        if(rit != rbegin && curr_pow != 0)
            os << " + " << *rit << "x^" << curr_pow;
        else if(rit == rbegin && curr_pow != 0)
            os << *rit << "x^" << curr_pow;
        else 
            os << " + " << *rit;

        --curr_pow;
    }   

    os << std::endl;
    return os;
}

}; // namespace poly
}; // namespace math
