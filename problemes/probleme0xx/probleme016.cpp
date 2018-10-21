#include <maths/puissance.h>
#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(16, "Power digit sum") {
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    nombre resultat = chiffres::somme_chiffres(puissance::puissance<nombre>(2, 1000u));
    return resultat.str();
}
