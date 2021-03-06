#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

#include <fstream>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(193, "Squarefree Numbers") {
    // A positive integer n is called squarefree, if no square of a prime divides n, thus 1, 2, 3, 5, 6, 7, 10, 11 are
    // squarefree, but not 4, 8, 9, 12.
    //
    // How many squarefree numbers are there below 2^50?
    auto limite = puissance::puissance<long long, unsigned>(2, 25);
    vecteur premiers;
    premiers::crible235<nombre>(static_cast<size_t>(limite), std::back_inserter(premiers));

    // N=2^50-1;
    // sum(k=1,sqrt(N),floor(N/k^2)*moebius(k))

    nombre resultat = 0;
    for (nombre k = 1; k < limite; ++k) {
        resultat += arithmetique::moebius(k, premiers) * limite * limite / (k * k);
    }

    return std::to_string(resultat);
}
