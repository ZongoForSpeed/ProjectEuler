#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <execution>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(136, "Singleton difference") {
    // The positive integers, x, y, and z, are consecutive terms of an arithmetic progression. 
    // Given that n is a positive integer, the equation, x² − y² − z² = n, has exactly one solution when n = 20:
    //
    //                                          13² − 10² − 7² = 20
    //
    // In fact there are twenty-five values of n below one hundred for which the equation has a unique solution.
    //
    // How many values of n less than fifty million have exactly one solution?
    nombre limite = 50000000;
    vecteur compteur(limite, 0);

    for (nombre x = 1; x < limite; ++x) {
        for (nombre m = (x + 2) / 3; m < limite; ++m) {
            if (nombre n = (m + x) * (3 * m - x);n < limite)
                compteur[n]++;
            else
                break;
        }
    }

    auto resultat = std::count(std::execution::par, compteur.begin(), compteur.end(), 1);
    return std::to_string(resultat);
}
