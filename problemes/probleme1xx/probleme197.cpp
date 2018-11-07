#include "problemes.h"
#include "arithmetique.h"
#include <fstream>

typedef unsigned long long nombre;

namespace {
    long double f(long double x) {
        return std::floor(std::pow(2.0L, 30.403243784L - x * x)) * 0.000000001L;
    }
}

ENREGISTRER_PROBLEME(197, "Investigating the behaviour of a recursively defined sequence") {
    // Given is the function f(x) = ⌊2^(30.403243784-x²)⌋ × 10-9 ( ⌊ ⌋ is the floor-function), the sequence un is
    // defined by u_0 = -1 and u_n+1 = f(u_n).
    // 
    // Find u_n + u_n+1 for n = 1012.
    // Give your answer with 9 digits after the decimal point.
    long double u_n = -1.0L;
    long double u_n1 = f(u_n);
    long double resultat = 0.0L;
    while (true) {
        long double u_n2 = f(u_n1);
        if (std::abs(u_n2 - u_n) < std::numeric_limits<long double>::epsilon()) {
            resultat = u_n + u_n1;
            break;
        }
        u_n = u_n1;
        u_n1 = u_n2;
    }

    return std::to_string(resultat, 9);
}
