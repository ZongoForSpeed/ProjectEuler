#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(119, "Digit power sum") {
    // The number 512 is interesting because it is equal to the sum of its digits raised to some power: 5 + 1 + 2 = 8,
    // and 8^3 = 512. Another example of a number with this property is 614656 = 28^4.
    //
    // We shall define an to be the nth term of this sequence and insist that a number must contain at least two digits
    // to have a sum.
    //
    // You are given that a2 = 512 and a10 = 614656.
    // 
    // Find a30.
    nombre taille = 18;
    nombre borne = puissance::puissance(10ULL, taille);

    vecteur resultat;
    for (nombre d = 2; d < 9 * taille; ++d) {
        for (nombre n = d; n < borne; n *= d) {
            if (n > 10 && chiffres::somme_chiffres(n) == d)
                resultat.push_back(n);
        }
    }

    std::sort(resultat.begin(), resultat.end());

    return std::to_string(resultat[29]);
}
