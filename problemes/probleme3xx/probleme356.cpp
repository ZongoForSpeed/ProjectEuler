#include "../problemes.h"
#include "numerique.h"
#include "premiers.h"
#include "matrice.h"

#include "mpz_nombre.h"

namespace {
    mpz_nombre calcul_solution(const mpz_nombre &p, const mpz_nombre &q, const unsigned long exposant, const mpz_nombre &modulo) {
        matrice::vecteur<mpz_nombre> init(3);
        init <<= 3, p, (p * p) % modulo;

        matrice::matrice<mpz_nombre> m(3, 3);
        m <<= 0, 0, modulo - (q % modulo),
              1, 0, 0,
              0, 1, p % modulo;

        m = matrice::puissance_matrice(m, exposant - 2, modulo);
        auto resultat = boost::numeric::ublas::prod(init, m);

        // std::cout << resultat << " " << resultat(2) <<  std::endl;
        return resultat(2) % modulo;
    }
}

ENREGISTRER_PROBLEME(356, "Largest roots of cubic polynomials") {
    // Let an be the largest real root of a polynomial g(x) = x^3 - 2^n·x^2 + n.
    //For example, a2 = 3.86619826...
    //
    //Find the last eight digits of Sum i=1..30 |a_i^987654321|.
    //
    //Note: |a| represents the floor function.
    mpz_nombre modulo = 100'000'000;
    unsigned long exposant = 987'654'321;
    mpz_nombre resultat = 0;
    for (long i = 1; i <= 30; ++i) {
        resultat += calcul_solution(1u << i, i, exposant, modulo) - 1;
        resultat %= modulo;
    }

    return std::to_string(resultat);
}
