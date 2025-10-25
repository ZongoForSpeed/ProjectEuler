#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "combinatoire.h"
#include "racine.h"

#include <execution>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool est_premier(nombre n, const std::set<nombre> &premiers) {
        if (premiers.contains(n))
            return true;
        if (n < *premiers.rbegin())
            return false;

        for (nombre p: premiers) {
            if (p * p > n)
                return true;
            if (n % p == 0)
                return false;
        }

        return true;
    }

    template<typename Iterator>
    void enumerate(nombre x, nombre phi, Iterator debut, Iterator fin, vecteur &resultat) {
        if (phi == 1)
            resultat.push_back(x);

        for (auto it = debut; it != fin; ++it) {
            nombre p = *it;
            if (phi % (p - 1) == 0) {
                enumerate(x * p, phi / (p - 1), debut, it, resultat);

                nombre _x = x * p;
                nombre _phi = phi / (p - 1);

                while (_phi % p == 0) {
                    _phi /= p;
                    _x *= p;

                    enumerate(_x, _phi, debut, it, resultat);
                }
            }
        }
    }
}

ENREGISTRER_PROBLEME(248, "Numbers for which Euler’s totient function equals 13!") {
    // The first number n for which φ(n)=13! is 6227180929.
    //
    // Find the 150,000th such number.
    const nombre phi = combinatoire::factorielle_ull(13ULL);

    std::set<nombre> premiers;
    premiers::crible235<nombre>(racine::racine_carre(phi), std::inserter(premiers, premiers.begin()));

    vecteur facteurs;
    auto diviseurs = arithmetique::diviseurs(phi, premiers);
    for (nombre d: diviseurs) {
        if (est_premier(d + 1, premiers))
            facteurs.push_back(d + 1);
    }

    vecteur resultat;
    enumerate(1, phi, facteurs.begin(), facteurs.end(), resultat);
    std::ranges::sort(resultat);

    return std::to_string(resultat[150000 - 1]);
}
