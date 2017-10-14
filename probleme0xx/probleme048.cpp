#include "problemes.h"
#include "arithmetiques.h"
#include "mp_nombre.h"

ENREGISTRER_PROBLEME(48, "Self powers") {
    // The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
    //
    // Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    mp_nombre resultat = 0;
    for (size_t n = 1; n <= 1000; ++n) {
        resultat += mp_nombre::puissance_modulaire(n, n, 10000000000LL);
        resultat %= 10000000000LL;
    }

    return resultat.to_string();
}
