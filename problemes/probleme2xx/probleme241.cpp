#include <numeric>
#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

typedef boost::multiprecision::cpp_int nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

namespace {
    void solution(const vecteur &premiers,
                  const nombre &limite,
                  const nombre &n,
                  const fraction &sigma,
                  vecteur &resultat) {
        std::map<nombre, unsigned long> decomposition;
        arithmetique::decomposition(sigma.numerator(), premiers, decomposition);

        nombre p = decomposition.begin()->first;
        unsigned long exposant = decomposition.begin()->second;

        if (n % p == 0)
            return;

        for (unsigned long a = exposant;; ++a) {
            nombre m = n * puissance::puissance<nombre>(p, a);
            if (m > limite)
                break;

            fraction sigma2 = fraction(puissance::puissance<nombre>(p, a + 1) - 1, puissance::puissance<nombre>(p, a) * (p - 1)) * sigma;

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
    const nombre limite = puissance::puissance<nombre>(10, 18);
    vecteur premiers;
    premiers::crible235<nombre>(1000, std::back_inserter(premiers));

    vecteur resultats;
    for (nombre k = 1; k < 6; ++k)
        solution(premiers, limite, 1, fraction(2, 2 * k + 1), resultats);

    std::sort(resultats.begin(), resultats.end());
    std::cout << resultats << std::endl;

    nombre resultat = std::accumulate(resultats.begin(), resultats.end(), nombre(0));
    return resultat.str();
}
