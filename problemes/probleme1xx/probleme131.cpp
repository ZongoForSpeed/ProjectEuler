#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(131, "Prime cube partnership") {
    // There are some prime values, p, for which there exists a positive integer, n, such that the expression
    // n^3 + n^2p is a perfect cube.
    //
    // For example, when p = 19, 8^3 + 8^2×19 = 12^3.
    // 
    // What is perhaps most surprising is that for each prime with this property the value of n is unique, and there are
    // only four such primes below one-hundred.
    //
    // How many primes below one million have this remarkable property?
    nombre limite = 1000000;
    std::set<nombre> premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));

    nombre resultat = 0;
    for (nombre a = 1; 3 * a * a < limite; ++a) {
        nombre b = a + 1;
        nombre p = b * b * b - a * a * a;
        if (p < limite && premiers.find(p) != premiers.end())
            ++resultat;
    }

    return std::to_string(resultat);
}

