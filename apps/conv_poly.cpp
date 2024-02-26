#include <vector>
#include <iostream>
#include "poly/poly.hpp"
using namespace math::poly;

int main() {
    std::vector<double> vec{1, 2, 3};
    Polynomial<double> poly(vec);

    poly.Dump();

    return 0;
}
