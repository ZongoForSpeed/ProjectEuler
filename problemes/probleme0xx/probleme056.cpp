#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "puissance.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(56, "Powerful digit sum") {
    // A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost 
    // unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the 
    // digits in each number is only 1.
    //
    // Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
    nombre maximum = 0;
    for (unsigned long a = 1; a < 100; ++a)
        for (unsigned long b = 1; b < 100; ++b) {
            nombre somme = chiffres::somme_chiffres(puissance::puissance<nombre>(a, b));
            maximum = std::max(maximum, somme);
        }
    return maximum.str();
}
