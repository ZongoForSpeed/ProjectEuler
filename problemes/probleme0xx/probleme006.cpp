#include "problemes.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(6, "Sum square difference") {
    // The sum of the squares of the first ten natural numbers is, 1² + 2² + ... + 10² = 385
    // The square of the sum of the first ten natural numbers is, (1 + 2 + ... + 10)² = 55² = 3025
    // Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is
    // 3025 − 385 = 2640.
    //
    // Find the difference between the sum of the squares of the first one hundred natural numbers 
    // and the square of the sum.
    nombre somme = 0;
    nombre somme_carre = 0;
    for (nombre n = 1; n < 101; ++n) {
        somme += n;
        somme_carre += n * n;
    }
    nombre solution = somme * somme - somme_carre;
    return std::to_string(solution);
}
