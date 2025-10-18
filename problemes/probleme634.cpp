#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "racine.h"
#include "premiers.h"

#include <set>

namespace {
    size_t facteurs_non_cube(size_t n, std::set<size_t>::const_iterator it, std::set<size_t>::const_iterator en) {
        size_t compteur = n;
        for (; it != en; ++it) {
            size_t p = *it;
            size_t p3 = p * p * p;
            if (p3 > n) {
                break;
            }
            compteur -= facteurs_non_cube(n / p3, std::next(it), en);
        }
        return compteur;
    }

    size_t F(size_t n, const std::set<size_t> &premiers) {
        size_t resultat = 0;

        // Si x n'est pas un carré alors il s'écrit de la forme a²b³ où b est n'est pas divisible par un nombre carré
        for (size_t b = 2; b * b * b * 4 <= n; ++b) {
            if (arithmetique::facteur_carre(b, premiers)) continue;
            resultat += racine::racine_carre(n / (b * b * b)) - 1;
        }

        // Si x est carré alors il est de la forme a² * b^6
        for (size_t b = 2; puissance::puissance(b, 6) <= n; ++b) {
            resultat += facteurs_non_cube(racine::racine_carre(n / puissance::puissance(b, 6)),
                                          premiers.begin(), premiers.end())
                        - (premiers.find(b) != premiers.end());
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(634, "Numbers of the form a²b³") {
    // Define F(n) to be the number of integers x <= n that can be written in the form x = a²b³, where a and b are
    // integers not necessarily different and both greater than 1.
    //
    // For example, 32 = 2² x 2³ and 72 = 3² x 2³ are the only two integers less than 100 that can be written in this
    // form. Hence, F(100) = 2.
    //
    // Further you are given F(2 x 10^4) = 130 and F(3 x 10^6) = 2014.
    //
    //Find F(9 x 10^18).
    const size_t limite = 9'000'000'000'000'000'000;

    std::set<size_t> premiers;
    premiers::crible235<size_t>(racine::racine_cubique<size_t>(limite), std::inserter(premiers, premiers.begin()));

    std::cout << "F(100) = " << F(100, premiers) << std::endl;
    std::cout << "F(20'000) = " << F(20'000, premiers) << std::endl;
    std::cout << "F(3'000'000) = " << F(3'000'000, premiers) << std::endl;

    return std::to_string(F(limite, premiers));
}
