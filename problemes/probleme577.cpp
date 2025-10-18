#include "problemes.h"

#include <iostream>

typedef unsigned long long nombre;

namespace {
    nombre H(nombre n) {
        // H(n) = ∑i(n−3i+1)(n−3i+2)/2 i=1..n/3 
        nombre total = 0;
        for (nombre i = 1; i < n / 3 + 1; ++i) {
            total += i * (n - 3*i + 1)*(n - 3*i + 2) / 2;
        }
        
        return total;
    }
}

ENREGISTRER_PROBLEME(577, "Counting hexagons") {
    // An equilateral triangle with integer side length n≥3n≥3 is divided into n2n2 equilateral triangles with side length 1 as shown in the diagram below.
    // The vertices of these triangles constitute a triangular lattice with (n+1)(n+2)/2 lattice points.
    //
    // Let H(n)H(n) be the number of all regular hexagons that can be found by connecting 6 of these points.
    //
    // p577_counting_hexagons.png
    // For example, H(3)=1, H(6)=12 and H(20)=966.
    //
    // Find ∑H(n) n=3..12345.
    // size_t limite = 100'000'000;
    std::cout << "H(3) = " << H(3) << std::endl;
    std::cout << "H(6) = " << H(6) << std::endl;
    std::cout << "H(20) = " << H(20) << std::endl;
    
    nombre m = 12345;
    nombre solution = 0;
    for (size_t n = 1; n < m + 1; ++n) {
        solution += H(n);
    }
    
    return std::to_string(solution);
}
