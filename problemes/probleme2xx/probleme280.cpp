#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "matrice.h"
#include "utilitaires.h"

#include <bitset>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double algorithme(std::map<std::tuple<size_t, size_t, size_t, size_t>, long double> &cache, size_t sx, size_t sy, const std::bitset<5> &haut, const std::bitset<5> &bas) {
        auto clef = std::make_tuple(sx, sy, haut.to_ulong(), bas.to_ulong());

        if (auto it = cache.find(clef);it != cache.end())
            return it->second;

        matrice::matrice<long double> A(25, 25, 0);
        matrice::vecteur<long double> b(25, 0);

        for (size_t x = 0; x < 5; ++x)
            for (size_t y = 0; y < 5; ++y) {
                size_t p = x + 5 * y;
                A(p, p) = 1;

                if (y == 0 && bas.test(x)) {
                    if (haut.none())
                        continue;
                    auto _bas = bas;
                    _bas.reset(x);
                    b(p) = algorithme(cache, x, 4 - y, _bas, haut);
                    continue;
                }

                size_t t = 0;

                if (x < 4) ++t;
                if (x > 0) ++t;
                if (y < 4) ++t;
                if (y > 0) ++t;

                long double f = 1.0L / t;

                b(p) = 1;
                if (x < 4) A(p, x + 1 + y * 5) = -f;
                if (x > 0) A(p, x - 1 + y * 5) = -f;
                if (y < 4) A(p, x + y * 5 + 5) = -f;
                if (y > 0) A(p, x + y * 5 - 5) = -f;
            }

        matrice::vecteur<long double> c(25, 0);
        // Résolution système A.c = b
        matrice::resolutionLU(A, b, c);

        long double resultat = c(sx + sy * 5);
        cache[clef] = resultat;

        return resultat;
    }
}

ENREGISTRER_PROBLEME(280, "Ant and seeds") {
    // A laborious ant walks randomly on a 5x5 grid. The walk starts from the central square. At each step, the ant
    // moves to an adjacent square at random, without leaving the grid; thus there are 2, 3 or 4 possible moves at each
    // step depending on the ant's position.
    //
    // At the start of the walk, a seed is placed on each square of the bas row.
    // When the ant isn't carrying a seed and reaches a square of the bas row containing a seed, it will start to carry
    // the seed. The ant will drop the seed on the first empty square of the haut row it eventually reaches.
    // 
    // What's the expected number of steps until all seeds have been dropped in the top row?
    // 
    // Give your answer rounded to 6 decimal places.
    std::map<std::tuple<size_t, size_t, size_t, size_t>, long double> cache;
    long double resultat = algorithme(cache, 2, 2, 31, 31);

    return format::to_fixed(resultat, 6);
}
