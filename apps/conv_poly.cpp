#include <list>
#include <iostream>
#include "poly/poly.hpp"
using namespace math::poly;

int main() {
    std::list<double> lst1{1, 2, 3};
    std::list<double> lst2{1, 2, 3};
    Polynomial<double> poly1(lst1);
    Polynomial<double> poly2(lst2);
    
    auto poly3 = poly1 + poly2;

    poly3.Dump();

    return 0;
}
