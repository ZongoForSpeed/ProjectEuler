#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(92, "Square digit chains") {
    // A number chain is created by continuously adding the square of the digits in a number to form a new number until
    // it has been seen before.
    //
    // For example,
    // 
    //      44 → 32 → 13 → 10 → 1 → 1
    //      85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89
    //
    // Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that
    // EVERY starting number will eventually arrive at 1 or 89.
    //
    // How many starting numbers below ten million will arrive at 89?
    nombre resultat = 0;
    for (nombre n = 1; n < 10000000; ++n) {
        nombre m = n;
        while (m != 89 && m != 1) {
            nombre s = 0;
            chiffres::boucle_chiffre(m, [&s](nombre d) { s += d * d; });
            m = s;
        }
        if (m == 89)
            ++resultat;
    }

    return std::to_string(resultat);
}
