#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "puissance.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(56, "Powerful digit sum") {
    // A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost 
    // unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the 
    // digits in each number is only 1.
    //
    // Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
    mpz_nombre maximum = 0;
    for (unsigned long a = 1; a < 100; ++a)
        for (unsigned long b = 1; b < 100; ++b) {
            mpz_nombre somme = mpz_nombre::puissance(a, b).somme_chiffres();
            maximum = std::max(maximum, somme);
        }
    return maximum.to_string();
}
