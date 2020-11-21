#include "problemes.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(493, "Under The Rainbow") {
    // 70 colored balls are placed in an urn, 10 for each of the seven rainbow colors.
    //
    // What is the expected number of distinct colors in 20 randomly picked balls?
    //
    // Give your answer with nine digits after the decimal point (a.bcdefghij).
    double resultat = 7 * (1.0 - mpz_nombre::coefficient_binomial(60, 20).get_double()
                                 / mpz_nombre::coefficient_binomial(70, 20).get_double());
    return std::to_fixed(resultat, 9);
}
