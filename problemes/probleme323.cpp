#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique.h"

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double probabilite(size_t n) {
        return puissance::puissance<long double>(1 - puissance::puissance<long double>(0.5L, n), 32u);
    }
}

ENREGISTRER_PROBLEME(323, "Bitwise-OR operations on random integers") {
    // Let y0, y1, y2,... be a sequence of random unsigned 32 bit integers (i.e. 0 ≤ yi < 2**32, every value equally
    // likely).
    // 
    // For the sequence xi the following recursion is given:
    //
    // x0 = 0 and
    // xi = xi-1 | yi-1, for i > 0. ( | is the bitwise-OR operator)
    // It can be seen that eventually there will be an index N such that xi = 2**32 -1 (a bit-pattern of all ones) 
    // for all i ≥ N.
    //
    // Find the expected value of N. Give your answer rounded to 10 digits after the decimal point.
    long double sum = 0;
    for (size_t n = 1;; ++n) {
        long double p = probabilite(n) - probabilite(n - 1);
        if (p < 1e-20L)
            break;
        sum += n * p;
    }

    return std::to_string(sum, 10);
}
