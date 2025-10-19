#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "mpf_nombre.h"
#include "polynome.h"

namespace {

    mpf_nombre pi(size_t x, const mpf_nombre &q) {
        return 1 - x / q;
    }

    mpf_nombre qi(size_t x, const mpf_nombre &q) {
        return x / q;
    }

    mpf_nombre T(size_t i, size_t n, const mpf_nombre &q) {
        mpf_nombre resultat = 0;
        for (size_t j = 1; j <= n; ++j) {
            resultat += std::pow(pi(j, q) / qi(j, q), i);
        }
        return resultat;
    }

    short parite(size_t i) {
        return i % 2 == 0 ? 1 : -1;
    }

    mpf_nombre P(size_t k, size_t n, const mpf_nombre &q) {
        std::vector<mpf_nombre> Pk{1};
        for (size_t i = 1; i <= n; ++i)
            Pk.front() *= qi(i, q);

        for (size_t i = 1; i <= k; ++i) {
            mpf_nombre pk = 0;
            for (size_t j = 1; j <= i; ++j) {
                pk += parite(j - 1) * Pk.at(i - j) * T(j, n, q);
            }
            pk /= i;
            Pk.emplace_back(pk);
        }

        return Pk.back();
    }
}


ENREGISTRER_PROBLEME(286, "Scoring probabilities") {
    // Barbara is a mathematician and a basketball player. She has found that the probability of scoring a point when
    // shooting from a distance x is exactly (1 - x/q), where q is a real constant greater than 50.
    //
    // During each practice run, she takes shots from distances x = 1, x = 2, ..., x = 50 and, according to her records,
    // she has precisely a 2 % chance to score a total of exactly 20 points.
    //
    // Find q and give your answer rounded to 10 decimal places.
    std::cout << std::setprecision(15);
    mpf_nombre::setPrecision(256);
    size_t n = 50;
    long double objectif = 0.02L;
    mpf_nombre limite;
    mpf_nombre::puissance(limite, 10, 11);
    mpf_nombre::inverse(limite, limite);
    mpf_nombre dq2 = 1;
    mpf_nombre q2 = 50;

    while (dq2 > limite) {
        // https://fr.wikipedia.org/wiki/Loi_Poisson_binomiale
        const auto p2 = P(20, n, q2 + dq2);
        if (p2 < objectif) {
            dq2 /= 10.0;
        } else {
            q2 += dq2;
        }
    }

    return format::to_fixed(q2, 10);
}
