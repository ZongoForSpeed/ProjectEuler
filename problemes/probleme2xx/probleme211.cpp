#include "problemes.h"
#include "polygonal.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(211, "Divisor Square Sum") {
    // For a positive integer n, let σ2(n) be the sum of the squares of its divisors. For example,
    //
    // σ2(10) = 1 + 4 + 25 + 100 = 130.
    // Find the sum of all n, 0 < n < 64,000,000 such that σ2(n) is a perfect square.
    nombre limite = 64000000;
    nombre resultat = 1;
    vecteur tableau(limite, 1);

    for (nombre d = 2; d < limite; ++d) {
        nombre d2 = d * d;
        for (nombre q = d; q < limite; q += d)
            tableau[q] += d2;

        if (polygonal::est_carre(tableau[d]))
            resultat += d;
    }

    return std::to_string(resultat);
}
