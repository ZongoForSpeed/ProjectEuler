#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <execution>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(135, "Same differences") {
    // Given the positive integers, x, y, and z, are consecutive terms of an arithmetic progression, the least value of
    // the positive integer, n, for which the equation, x² − y² − z² = n, has exactly two solutions is n = 27:
    //
    //                              34² − 27² − 20² = 12² − 9² − 6² = 27
    //
    // It turns out that n = 1155 is the least value which has exactly ten solutions.
    // 
    // How many values of n less than one million have exactly ten distinct solutions?
    nombre limite = 1000000;
    vecteur compteur(limite, 0);

    for (nombre x = 1; x < limite; ++x) {
        for (nombre m = (x + 2) / 3; m < limite; ++m) {
            if (nombre n = (m + x) * (3 * m - x);n < limite)
                compteur[n]++;
            else
                break;
        }
    }

    auto resultat = std::count(std::execution::par, compteur.begin(), compteur.end(), 10);
    return std::to_string(resultat);
}
