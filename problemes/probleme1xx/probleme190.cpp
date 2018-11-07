#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(190, "Maximising a weighted product") {
    // Let Sm = (x1, x2, ... , xm) be the m-tuple of positive real numbers with x1 + x2 + ... + xm = m for which
    // Pm = x1 * x2² * ... * xm^m is maximised.
    //
    // For example, it can be verified that [P10] = 4112 ([ ] is the integer part function).
    //
    // Find Σ[Pm] for 2 ≤ m ≤ 15.
    nombre resultat = 0;
    for (nombre m = 2; m <= 15; ++m) {
        long double produit = 1;
        for (nombre i = 1; i <= m; ++i) {
            produit *= puissance::puissance(static_cast<long double>(2 * i) / (m + 1), i);
        }
        resultat += std::floor(produit);
    }

    return std::to_string(resultat);
}
