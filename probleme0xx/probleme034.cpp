#include "problemes.h"
#include "chiffres.h"
#include "combinatoire.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(34, "Digit factorials") {
    // 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
    //
    // Find the sum of all numbers which are equal to the sum of the factorial of their digits.
    //
    // Note: as 1! = 1 and 2! = 2 are not sums they are not included.
    nombre borne = 2540160; // 7*9!
    nombre solution = 0;
    for (nombre n = 10; n < borne; ++n) {
        nombre s = 0;
        chiffres::boucle_chiffre(n, [&s](nombre d) { s += combinatoire::factorielle(d); });
        if (s == n) solution += n;
    }
    return std::to_string(solution);
}
