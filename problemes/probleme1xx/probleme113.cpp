#include "problemes.h"
#include "combinatoire.h"

#include <fstream>
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(113, "Non-bouncy numbers") {
    // Working from left-to-right if no digit is exceeded by the digit to its left it is called an increasing number;
    // for example, 134468.
    //
    // Similarly if no digit is exceeded by the digit to its right it is called a decreasing number; for example, 66420.
    //
    // We shall call a positive integer that is neither increasing nor decreasing a "bouncy" number; for example, 155349.
    //
    // As n increases, the proportion of bouncy numbers below n increases such that there are only 12951 numbers below
    // one-million that are not bouncy and only 277032 non-bouncy numbers below 10^10.
    //
    // How many numbers below a googol (10^100) are not bouncy?
    size_t longueur = 100;
    mpz_nombre resultat = 0;

    for (size_t n = 0; n < longueur; ++n)
        for (size_t d = 0; d < 10; ++d)
            resultat += mpz_nombre::coefficient_binomial(n + d, d);

    for (size_t n = 0; n < longueur; ++n)
        for (size_t d = 0; d < 9; ++d)
            resultat += mpz_nombre::coefficient_binomial(n + d, d);

    resultat -= 10 * longueur;

    return resultat.to_string();
}
