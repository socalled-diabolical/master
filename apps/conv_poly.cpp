#include <vector>
#include <iostream>
#include "poly/poly.hpp"
#include <complex>

using namespace math::poly;

int main() {
    
    std::vector<std::complex<double>> lst1{1, 2, 3, 4};
    std::vector<std::complex<double>> lst2{1, 2, 3};
    Polynomial<std::complex<double>> poly1(lst1);
    Polynomial<std::complex<double>> poly2(lst2);
    
    auto poly3 = poly1 + poly2;

    poly3.Dump();

    std::cout << "poly3(2) = " <<  poly3(std::complex<double>(2, 0)) << std::endl;

    return 0;
}
