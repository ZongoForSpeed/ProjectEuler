#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

#include <fstream>
#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(108, "Diophantine reciprocals I") {
    // In the following equation x, y, and n are positive integers.
    //
    //                                          1/x + 1/y = 1/n
    //
    // For n = 4 there are exactly three distinct solutions:
    //
    //      1/5 + 1/20 = 1/4
    //      1/6 + 1/12 = 1/4
    //      1/8 + 1/8 = 1/4
    //
    // What is the least value of n for which the number of distinct solutions exceeds one-thousand?
    //
    // NOTE: This problem is an easier version of Problem 110; it is strongly advised that you solve this one first.
    vecteur premiers;
    premiers::crible23<nombre>(1000000, std::back_inserter(premiers));

    nombre resultat = 0;
    for (nombre n = 2;; ++n) {
        std::map<nombre, nombre> decomposition;
        arithmetique::decomposition(n, premiers, decomposition);
        nombre solutions = 1;
        for (const auto &d: decomposition) {
            solutions *= (2 * d.second + 1);
        }
        solutions = (solutions + 1) / 2;
        if (solutions > 1000) {
            resultat = n;
            break;
        }
    }

    return std::to_string(resultat);
}
