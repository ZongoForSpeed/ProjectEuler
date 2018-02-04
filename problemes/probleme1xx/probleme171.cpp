#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(171, "Finding numbers for which the sum of the squares of the digits is a square") {
    // For a positive integer n, let f(n) be the sum of the squares of the digits (in base 10) of n, e.g.
    //
    //      f(3) = 3² = 9,
    //      f(25) = 2² + 5² = 4 + 25 = 29,
    //      f(442) = 4² + 4² + 2² = 16 + 16 + 4 = 36
    //
    // Find the last nine digits of the sum of all n, 0 < n < 10^20, such that f(n) is a perfect square.
    nombre masque = 1000000000ULL;
    nombre limite = 20;

    vecteur combinaison{1};
    vecteur somme{0};

    for (nombre n = 0; n < limite; ++n) {
        vecteur n_somme(somme.size() + 81, 0);

        if (n > 8) {
            for (nombre i = 0; i < somme.size(); ++i)
                for (nombre j = 0; j < 10; ++j)
                    n_somme[i + j * j] += somme[i];
        } else {
            vecteur n_combinaison(combinaison.size() + 81, 0);
            for (nombre i = 0; i < somme.size(); ++i) {
                if (combinaison[i] != 0) {
                    for (nombre j = 0; j < 10; ++j) {
                        n_combinaison[i + j * j] += combinaison[i];
                        n_somme[i + j * j] += somme[i] + combinaison[i] * j * puissance::puissance(10UL, n);
                    }
                }
            }
            std::swap(n_combinaison, combinaison);
        }

        for (nombre &s: n_somme)
            s %= masque;
        std::swap(n_somme, somme);
    }

    nombre resultat = 0;
    for (nombre i = 1; i * i < somme.size(); ++i)
        resultat += somme[i * i] % masque;

    resultat %= masque;
    return std::to_string(resultat);
}
