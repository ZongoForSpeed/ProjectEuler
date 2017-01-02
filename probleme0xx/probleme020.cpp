#include "problemes.h"
#include "chiffres.h"
#include "combinatoire.h"
#include "utilitaires.h"
#include "grand_nombre.h"

ENREGISTRER_PROBLEME(20, "Factorial digit sum")
{
    // n! means n × (n − 1) × ... × 3 × 2 × 1
    // 
    // For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
    // and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
    // 
    // Find the sum of the digits in the number 100!
    grand_nombre factorielle = grand_nombre::factorielle(100);
    grand_nombre resultat = 0;
    chiffres::boucle_chiffre(factorielle, [&resultat](grand_nombre d) { resultat += d; });
    return resultat.to_string();
}
