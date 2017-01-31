#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "mp_nombre.h"

ENREGISTRER_PROBLEME(16, "Power digit sum")
{
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    mp_nombre resultat = mp_nombre::puissance(2, 1000).somme_chiffres();
    return resultat.to_string();
}
