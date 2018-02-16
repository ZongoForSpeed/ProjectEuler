#include "problemes.h"
#include "mp_nombre.h"

ENREGISTRER_PROBLEME(216, "Investigating the primality of numbers of the form 2n²-1") {
    // Consider numbers t(n) of the form t(n) = 2n²-1 with n > 1.
    // The first such numbers are 7, 17, 31, 49, 71, 97, 127 and 161.
    // It turns out that only 49 = 7*7 and 161 = 7*23 are not prime.
    // For n ≤ 10000 there are 2202 numbers t(n) that are prime.
    // 
    // How many numbers t(n) are prime for n ≤ 50,000,000 ?
    size_t limite = 50000000;
    size_t resultat = 0;
    for (size_t n = 1; n <= limite; ++n) {
        if (mp_nombre::premier(2 * n * n - 1, 25))
            ++resultat;
    }

    return std::to_string(resultat);
}