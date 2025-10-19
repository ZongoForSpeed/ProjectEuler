#include <numeric>
#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "format/vector.h"
#include "premiers.h"
#include "utilitaires.h"

#include <execution>
#include <boost/rational.hpp>

#include "mpq_fraction.h"

typedef std::vector<mpz_nombre> vecteur;

namespace {

    void solution(const std::vector<unsigned long long> &premiers,
                  const mpz_nombre &limite,
                  const mpz_nombre &n,
                  const mpq_fraction &sigma,
                  vecteur &resultat) {
        std::map<mpz_nombre, unsigned long> decomposition;
        arithmetique::decomposition(sigma.numerateur(), premiers, decomposition);

        mpz_nombre p = decomposition.begin()->first;
        unsigned long exposant = decomposition.begin()->second;

        if (n % p == 0)
            return;

        for (unsigned long a = exposant;; ++a) {
            mpz_nombre m = n * mpz_nombre::puissance(p, a);
            if (m > limite)
                break;

            mpq_fraction sigma2 = mpq_fraction(mpz_nombre::puissance(p, a + 1) - 1,
                                               mpz_nombre::puissance(p, a) * (p - 1)) * sigma;

            if (sigma2 == 1) {
                resultat.push_back(m);
                // std::cout << m << std::endl;
            } else if (sigma2.numerateur() > 1 && sigma2.denominateur() > 1) {
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
    auto limite = puissance::puissance<unsigned long long>(10, 18u);
    std::vector<unsigned long long> premiers;
    premiers::crible235<unsigned long long>(1000, std::back_inserter(premiers));

    vecteur resultats;
    for (size_t k = 1; k < 6; ++k)
        solution(premiers, limite, 1, mpq_fraction(2ul, 2u * k + 1u), resultats);

    std::sort(resultats.begin(), resultats.end());
    std::cout << resultats << std::endl;

    mpz_nombre resultat = std::reduce(std::execution::par, resultats.begin(), resultats.end());
    return resultat.to_string();
}
