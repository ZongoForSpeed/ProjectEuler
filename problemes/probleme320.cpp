#include "problemes.h"
#include "utilitaires.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "combinatoire.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool test_exposant(const nombre &p, const nombre &exposant, nombre n) {
        nombre e = 0;
        while (n != 0) {
            n /= p;
            e += n;
        }

        return e + 1 > exposant;
    }

    nombre calcul_exposant(const nombre &p, const nombre &exposant, const nombre &borne_inf) {
        // N(i - 1) ≤ N(i) ≤ 1234567890i
        nombre inferieur = borne_inf;
        nombre superieur = exposant * p;
        // while (!test_exposant(p, exposant, superieur)) superieur *= 2;
        while (inferieur < superieur) {
            nombre moyennne = (inferieur + superieur) / 2;
            if (!test_exposant(p, exposant, moyennne))
                inferieur = moyennne + 1;
            else
                superieur = moyennne;
        }
        return inferieur;
    }
}

ENREGISTRER_PROBLEME(320, "Factorials divisible by a huge integer") {
    // Let N(i) be the smallest integer n such that n! is divisible by (i!)**1234567890
    //
    // Let S(u)=∑N(i) for 10 ≤ i ≤ u.
    //
    // S(1000)=614538266565663.
    //
    // Find S(1 000 000) mod 10**18.
    const size_t limite = 1'000'000;
    const size_t exposant = 1'234'567'890;
    const auto modulo = puissance::puissance<nombre>(10, 18u);

    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));

    boost::multiprecision::cpp_int resultat = 0;

    std::map<nombre, size_t> decomposition;
    arithmetiques::decomposition(combinatoire::factorielle<nombre>(9), premiers, decomposition);

    nombre N = 0;
    for (nombre i = 10; i < limite + 1; ++i) {
        std::map<nombre, size_t> d;
        arithmetiques::decomposition(i, premiers, d);
        for (const auto &entry: d) {
            auto &e = decomposition[entry.first];
            e += entry.second;
            N = std::max(calcul_exposant(entry.first, e * exposant, N), N);
        }

        resultat += N;
    }

    std::cout << resultat << std::endl;
    resultat %= modulo;
    return resultat.str();
}
