#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(110, "Diophantine reciprocals II") {
    // In the following equation x, y, and n are positive integers.
    // 
    //                                          1/x + 1/y = 1/n
    //
    // It can be verified that when n = 1260 there are 113 distinct solutions and this is the least value of n for which
    // the total number of distinct solutions exceeds one hundred.
    // 
    // What is the least value of n for which the number of distinct solutions exceeds four million?
    // 
    // NOTE: This problem is a much more difficult version of Problem 108 and as it is well beyond the limitations of a
    // brute force approach it requires a clever implementation.
    nombre limite = 4000000;

    vecteur premiers;
    premiers::crible23<nombre>(limite * 3, std::back_inserter(premiers));

    nombre solutions = 0;
    nombre resultat = 0;
    while (solutions <= limite) {
        resultat += 2036934900; // 2^2 * 3^2 * 5^2 * 7^2 * 11 * 13 * 17

        std::map<nombre, size_t> decomposition;
        arithmetique::decomposition(resultat, premiers, decomposition);

        solutions = 1;
        for (auto d: decomposition)
            solutions *= (2 * d.second + 1);

        solutions /= 2;
    }

    return std::to_string(resultat);
}
