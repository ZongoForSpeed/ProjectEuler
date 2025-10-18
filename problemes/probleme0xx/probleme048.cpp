#include "problemes.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(48, "Self powers") {
    // The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
    //
    // Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    const size_t modulo = 10'000'000'000;
    mpz_nombre resultat = 0;
    for (unsigned long n = 1; n <= 1000; ++n) {
        resultat += mpz_nombre::puissance_modulaire(n, n, modulo);
    }
    resultat %= modulo;
    return std::to_string(resultat);
}
