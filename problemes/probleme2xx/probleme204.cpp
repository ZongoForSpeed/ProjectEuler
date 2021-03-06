#include "problemes.h"
#include "premiers.h"

#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(204, "Generalised Hamming Numbers") {
    // A Hamming number is a positive number which has no prime factor larger than 5.
    // So the first few Hamming numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15.
    // There are 1105 Hamming numbers not exceeding 10^8.
    //
    // We will call a positive number a generalised Hamming number of type n, if it has no prime factor larger than n.
    // Hence the Hamming numbers are the generalised Hamming numbers of type 5.
    //
    // How many generalised Hamming numbers of type 100 are there which don't exceed 10^9?
    nombre limite = 1000000000;
    nombre h = 100;
    vecteur premiers;
    premiers::crible2<nombre>(limite, std::back_inserter(premiers));

    std::vector<bool> Hamming(limite + 1, true);
    Hamming[0] = false;
    for (auto p: premiers) {
        if (p > h) for (nombre k = p; k < limite; k += p) Hamming[k] = false;
    }

    auto resultat = std::count(Hamming.begin(), Hamming.end(), true);
    return std::to_string(resultat);
}
