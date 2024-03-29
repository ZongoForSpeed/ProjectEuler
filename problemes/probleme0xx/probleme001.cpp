#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(1, "Multiples of 3 and 5") {
    // If we list all the natural numbers below 10 that are multiples of 3 or 5, 
    // we get 3, 5, 6 and 9. The sum of these multiples is 23.
    // 
    // Find the sum of all the multiples of 3 or 5 below 1000.
    nombre solution = 0;
#pragma unroll
    for (size_t n = 1; n < 1000; ++n) {
        if (n % 3 == 0 || n % 5 == 0)
            solution += n;
    }
    return std::to_string(solution);
}
