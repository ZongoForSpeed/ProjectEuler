#include "problemes.h"
#include "polygonal.h"
#include "mpz_nombre.h"

#include <sstream>
#include <vector>

typedef std::vector<mpz_nombre> vecteur;

ENREGISTRER_PROBLEME(80, "Square root digital expansion") {
    // It is well known that if the square root of a natural number is not an integer, then it is irrational. The
    // decimal expansion of such square roots is infinite without any repeating pattern at all.
    //
    // The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits
    // is 475.
    //
    // For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal
    // digits for all the irrational square roots.
    mpz_nombre gogol = mpz_nombre::puissance(10, 100u);

    std::ostringstream oss;
    for (size_t n = 1; n < 100; ++n) {
        if (!polygonal::est_carre(n)) {
            mpz_nombre carre = gogol * gogol * n;
            mpz_nombre::racine_carre(carre, carre);
            oss << carre.to_string().substr(0, 100);
        }
    }

    long resultat = 0;
    for (auto c: oss.str()) {
        resultat += (c - '0');
    }
    return std::to_string(resultat);
}
