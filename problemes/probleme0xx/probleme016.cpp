#include "problemes.h"
#include "chiffres.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(16, "Power digit sum") {
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    mpz_nombre resultat = mpz_nombre::puissance(2, 1000u).somme_chiffres();
    return resultat.to_string();
}
