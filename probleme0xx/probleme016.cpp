#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"
#include "nombre.h"

#include <iostream>

ENREGISTRER_PROBLEME(16, "Power digit sum")
{
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    nombre n = puissance::puissance<nombre, unsigned>(2, 1000);
    nombre resultat = 0;
    chiffres::boucle_chiffre(n, [&resultat](nombre d) { resultat += d; });
    return std::to_string(resultat);
}
