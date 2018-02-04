#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(268, "Counting numbers with at least four distinct prime factors less than 100") {
    // It can be verified that there are 23 positive integers less than 1000 that are divisible by at least four
    // distinct primes less than 100.
    //
    // Find how many positive integers less than 10**16 are divisible by at least four distinct primes less than 100.
    const auto N = puissance::puissance<nombre, unsigned>(10, 16);
    vecteur premiers;
    premiers::crible2<nombre>(100, std::back_inserter(premiers));

    vecteur produits;
    for (auto it1 = premiers.begin(), en = premiers.end(); it1 != en; ++it1)
        for (auto it2 = it1 + 1; it2 != en; ++it2)
            for (auto it3 = it2 + 1; it3 != en; ++it3)
                for (auto it4 = it3 + 1; it4 != en; ++it4) {
                    produits.push_back(*it1 * *it2 * *it3 * *it4);
                }

    nombre resultat = 0;
    for (size_t i = 4; !produits.empty(); ++i) {
        nombre somme = 0;
        std::set<nombre> suivants;
        for (auto pi: produits) {
            somme += N / pi;
            for (auto p : premiers) {
                if (pi % p != 0 && pi * p < N) suivants.insert(pi * p);
            }
        }

        somme *= (i - 1) * (i - 2) * (i - 3) / 6;

        if (i % 2 == 0)
            resultat += somme;
        else
            resultat -= somme;

        produits.assign(suivants.begin(), suivants.end());
    }

    return std::to_string(resultat);
}
