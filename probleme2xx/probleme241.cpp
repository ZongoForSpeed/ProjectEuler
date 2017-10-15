#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "mp_nombre.h"

typedef boost::rational<mp_nombre> fraction;
typedef std::vector<mp_nombre> vecteur;

namespace {
    void solution(const vecteur &premiers,
                  const mp_nombre &limite,
                  const mp_nombre &n,
                  const fraction &sigma,
                  vecteur &resultat) {
        std::map<mp_nombre, size_t> decomposition;
        arithmetiques::decomposition(sigma.numerator(), premiers, decomposition);

        mp_nombre p = decomposition.begin()->first;
        size_t exposant = decomposition.begin()->second;

        if (n % p == 0)
            return;

        for (size_t a = exposant;; ++a) {
            mp_nombre m = n * mp_nombre::puissance(p, a);
            if (m > limite)
                break;

            fraction sigma2 =
                    sigma * fraction(mp_nombre::puissance(p, a + 1) - 1, mp_nombre::puissance(p, a) * (p - 1));

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
    const mp_nombre limite = mp_nombre::puissance(10, 18);
    vecteur premiers;
    premiers::crible235<mp_nombre>(1000, std::back_inserter(premiers));

    vecteur resultats;
    for (mp_nombre k = 1; k < 6; ++k)
        solution(premiers, limite, 1, fraction(2, 2 * k + 1), resultats);

    std::sort(resultats.begin(), resultats.end());
    std::cout << resultats << std::endl;

    mp_nombre resultat = std::accumulate(resultats.begin(), resultats.end(), mp_nombre(0));
    return resultat.to_string();
}
