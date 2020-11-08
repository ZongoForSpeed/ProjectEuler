#include "problemes.h"
#include "timer.h"
#include "utilitaires.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"
#include "premiers.h"

namespace {
    // Resolution équation x^15 + 1 = 0 (mod p) où p est premier.
    // x^15 + 1 = 0 (mod p) <=> (-x)^15 = 1 (mod p).
    std::vector<size_t> resoudre_equation(size_t p, const std::vector<size_t> &premiers) {
        auto d = arithmetique::PGCD<size_t>(p - 1, 15);
        if (d == 1) {
            return std::vector<size_t>(1, p - 1);
        }

        if (auto racine = arithmetique::racine_primitive(p, premiers)) {
            auto h = puissance::puissance_modulaire(racine.value(), (p - 1) / d, p);
            std::vector<size_t> solutions;
            for (size_t n = 0; n < d; ++n) {
                solutions.push_back(p - puissance::puissance_modulaire(h, n, p));
            }
            // std::sort(solutions.begin(), solutions.end());
            return solutions;
        } else {
            std::cout << "ERREUR !!!!!!!!!!!!! : " << p << std::endl;
            return std::vector<size_t>(1, p - 1);
        }
    }
}

ENREGISTRER_PROBLEME(421, "Prime factors of n^15+1") {
    // Numbers of the form n15+1 are composite for every integer n > 1.
    // For positive integers n and m let s(n,m) be defined as the sum of the distinct prime factors of n15+1 not
    // exceeding m.
    //
    // E.g. 2^15+1 = 3×3×11×331.
    // So s(2,10) = 3 and s(2,1000) = 3+11+331 = 345.
    //
    // Also 10^15+1 = 7×11×13×211×241×2161×9091.
    //
    // So s(10,100) = 31 and s(10,1000) = 483.
    //
    // Find ∑ s(n,10^8) for 1 ≤ n ≤ 10^11.
    size_t limite_n = 100'000'000'000;
    size_t limite_p = 100'000'000;
    std::vector<size_t> premiers;

    {
        Timer t("Crible nombres premiers");
        premiers::crible235<size_t>(limite_p, std::back_inserter(premiers));
        auto it = std::upper_bound(premiers.begin(), premiers.end(), limite_p);
        premiers.erase(it, premiers.end());

        std::cout << premiers.size() << std::endl;
    }

    std::cout << std::boolalpha;

    size_t resultat = 0;
    for (size_t p: premiers) {
        auto solutions = resoudre_equation(p, premiers);
        size_t q = limite_n / p;
        size_t r = limite_n % p;

        auto reste_solution = std::count_if(solutions.begin(), solutions.end(), [&r](size_t s) { return s <= r; });
        resultat += p * (q * solutions.size() + static_cast<size_t>(reste_solution));

        // std::cout << p << "\t[" << (p % 3) << ", " << (p % 5) << "] \t=> " << solutions << std::endl;
    }

    return std::to_string(resultat);
}
