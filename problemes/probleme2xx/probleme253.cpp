#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "mpz_nombre.h"
#include "utilitaires.h"

#include <execution>
#include <numeric>

typedef std::vector<mpz_nombre> vecteur;
typedef std::map<mpz_nombre, mpz_nombre> dictionnaire;

namespace {
    dictionnaire algorithme(const vecteur &tailles, std::map<vecteur, dictionnaire> &cache) {
        if (auto it = cache.find(tailles);it != cache.end())
            return it->second;

        mpz_nombre somme = std::reduce(std::execution::par, tailles.begin(), tailles.end());
        if (somme == 1 && tailles[1] == 1) {
            dictionnaire resultat{{1, 1}};
            return resultat;
        } else {
            dictionnaire resultat;
            vecteur _tailles = tailles;

            for (size_t n = 0; n < tailles.size(); ++n) {
                if (tailles[n] == 0)
                    continue;
                --_tailles[n];
                if (n == 1) {
                    auto tmp = algorithme(_tailles, cache);
                    for (auto&[k, v]: tmp) {
                        if (k < somme)
                            resultat[somme] += v * tailles[n];
                        else
                            resultat[k] += v * tailles[n];
                    }
                } else {
                    for (size_t m1 = 0; m1 < n; ++m1) {
                        size_t m2 = n - m1 - 1;
                        if (m1 != 0) ++_tailles[m1];
                        if (m2 != 0) ++_tailles[m2];

                        auto tmp = algorithme(_tailles, cache);
                        for (auto&[k, v]: tmp) {
                            if (k < somme)
                                resultat[somme] += v * tailles[n];
                            else
                                resultat[k] += v * tailles[n];
                        }

                        if (m1 != 0) --_tailles[m1];
                        if (m2 != 0) --_tailles[m2];
                    }
                }

                ++_tailles[n];
            }

            cache.emplace(tailles, resultat);
            return resultat;
        }
    }
}

ENREGISTRER_PROBLEME(253, "Tidying up") {
    // A small child has a “number caterpillar” consisting of forty jigsaw pieces, each with one number on it, which,
    // when connected together in a line, reveal the numbers 1 to 40 in order.
    //
    // Every night, the child's father has to pick up the pieces of the caterpillar that have been scattered across the
    // play room. He picks up the pieces at random and places them in the correct order.
    // As the caterpillar is built up in this way, it forms distinct segments that gradually merge together.
    // The number of segments starts at zero (no pieces placed), generally increases up to about eleven or twelve, then
    // tends to drop again before finishing at a single segment (all pieces placed).
    //
    // For example:
    //
    //                      Piece Placed    Segments So Far
    //                      12              1
    //                      4	            2
    //                      29	            3
    //                      6	            4
    //                      34	            5
    //                      5	            4
    //                      35	            4
    //                      …	            …
    //
    // Let M be the maximum number of segments encountered during a random tidy-up of the caterpillar.
    // For a caterpillar of ten pieces, the number of possibilities for each M is
    // 
    //                                  M	Possibilities
    //                                  1	512      
    //                                  2	250912      
    //                                  3	1815264      
    //                                  4	1418112      
    //                                  5	144000      
    // so the most likely value of M is 3 and the average value is 385643⁄113400 = 3.400732, rounded to six decimal places.
    //
    // The most likely value of M for a forty-piece caterpillar is 11; but what is the average value of M?
    //
    // Give your answer rounded to six decimal places.
    size_t N = 40;

    vecteur input(N, 0);
    input.emplace_back(1);

    std::map<vecteur, dictionnaire> cache;
    auto combinaison = algorithme(input, cache);

    mpz_nombre numerateur = 0;
    mpz_nombre denominateur = 0;

    for (auto[k, v]: combinaison) {
        numerateur += k * v;
        denominateur += v;
    }

    const auto masque = puissance::puissance<size_t>(10, 7u);
    numerateur *= masque;
    numerateur /= denominateur;
    auto resultat = numerateur.get_double();
    resultat /= masque;
    return format::to_fixed(resultat, 6);
}
