#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"
#include "grand_nombre.h"

ENREGISTRER_PROBLEME(16, "Power digit sum")
{
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    grand_nombre n = grand_nombre::puissance(2, 1000);
    grand_nombre resultat = 0;
    chiffres::boucle_chiffre(n, [&resultat](grand_nombre d) { resultat += d; });
    return resultat.to_string();
}
