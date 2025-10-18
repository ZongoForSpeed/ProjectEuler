#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"
#include "puissance.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(134, "Prime pair connection") {
    // Consider the consecutive primes p1 = 19 and p2 = 23. It can be verified that 1219 is the smallest number such
    // that the last digits are formed by p1 whilst also being divisible by p2.
    //
    // In fact, with the exception of p1 = 3 and p2 = 5, for every pair of consecutive primes, p2 > p1, there exist
    // values of n for which the last digits are formed by p1 and n is divisible by p2. Let S be the smallest of these
    // values of n.
    //
    // Find ∑ S for every pair of consecutive primes with 5 ≤ p1 ≤ 1000000.
    nombre limite = 1000000;
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));

    nombre resultat = 0;
    for (nombre n = 0; n < premiers.size() - 1; ++n) {
        nombre p1 = premiers.at(n);
        nombre p2 = premiers.at(n + 1);
        if (p1 > 4 && p1 < limite) {
            nombre chiffres = chiffres::nombre_chiffres(p1);
            nombre b = puissance::puissance_modulaire<nombre>(10, chiffres * (p2 - 2), p2);
            b *= p2 - p1;
            b %= p2;
            resultat += b * puissance::puissance<nombre>(10, chiffres) + p1;
        }
    }
    return std::to_string(resultat);
}

