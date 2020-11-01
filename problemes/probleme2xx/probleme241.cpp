#include <numeric>
#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"

typedef boost::rational<uint128_t> fraction;
typedef std::vector<uint128_t> vecteur;

namespace {
    void solution(const vecteur &premiers,
                  const uint128_t &limite,
                  const uint128_t &n,
                  const fraction &sigma,
                  vecteur &resultat) {
        std::map<uint128_t, unsigned long> decomposition;
        arithmetique::decomposition(sigma.numerator(), premiers, decomposition);

        uint128_t p = decomposition.begin()->first;
        unsigned long exposant = decomposition.begin()->second;

        if (n % p == 0)
            return;

        for (unsigned long a = exposant;; ++a) {
            uint128_t m = n * puissance::puissance<uint128_t>(p, a);
            if (m > limite)
                break;

            fraction sigma2 = fraction(puissance::puissance<uint128_t>(p, a + 1) - 1,
                                       puissance::puissance<uint128_t>(p, a) * (p - 1)) * sigma;

            if (sigma2 == 1) {
                resultat.push_back(m);
                // std::cout << m << std::endl;
            } else if (sigma2.numerator() > 1 && sigma2.denominator() > 1) {
                solution(premiers, limite, m, sigma2, resultat);
            }
        }
    }
}

ENREGISTRER_PROBLEME(241, "Perfection Quotients") {
    // For a positive integer n, let σ(n) be the sum of all divisors of n, so e.g. σ(6) = 1 + 2 + 3 + 6 = 12.
    //
    // A perfect number, as you probably know, is a number with σ(n) = 2n.
    //
    // Let us define the perfection quotient of a positive integer as p(n) = σ(n)/n
    //
    // Find the sum of all positive integers n ≤ 1018 for which p(n) has the form k + 1/2, where k is an integer.
    auto limite = puissance::puissance<uint128_t>(10, 18u);
    vecteur premiers;
    premiers::crible235<uint128_t>(1000, std::back_inserter(premiers));

    vecteur resultats;
    for (uint128_t k = 1; k < 6; ++k)
        solution(premiers, limite, 1, fraction(2, 2 * k + 1), resultats);

    std::sort(resultats.begin(), resultats.end());
    std::cout << resultats << std::endl;

    uint128_t resultat = std::reduce(resultats.begin(), resultats.end());
    return std::to_string(resultat);
}
