#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(5, "Smallest multiple") {
    // 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
    // 
    // What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
    nombre solution = 2;
    for (nombre d = 3; d < 21; ++d) {
        solution = arithmetique::PPCM(d, solution);
    }
    return std::to_string(solution);
}
