#include "problemes.h"
#include "arithmetique.h"
#include "polynome.h"

#include <boost/serialization/nvp.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

typedef boost::multiprecision::cpp_bin_float_quad nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre puissance_float(nombre base, size_t exposant) {
        nombre resultat(1);
        while (exposant > 0) {
            if (exposant % 2)
                resultat *= base;
            exposant /= 2;
            base = base * base;
        }
        return resultat;
    }

    nombre pi(size_t x, const nombre &q) {
        return nombre(1.0) - x / q;
    }

    nombre qi(size_t x, const nombre &q) {
        return x / q;
    }

    nombre T(size_t i, size_t n, const nombre &q) {
        nombre resultat = 0;
        for (size_t j = 1; j <= n; ++j) {
            resultat += puissance_float(pi(j, q) / qi(j, q), i);
        }
        return resultat;
    }

    template<typename Nombre>
    short parite(Nombre i) {
        if (i % 2 == 0)
            return 1;
        else
            return -1;
    }

    nombre P(size_t k, size_t n, const nombre &q) {
        std::vector<nombre> Pk{1};
        for (size_t i = 1; i <= n; ++i)
            Pk.front() *= qi(i, q);

        for (size_t i = 1; i <= k; ++i) {
            nombre pk = 0;
            for (size_t j = 1; j <= i; ++j) {
                pk += parite(j - 1) * Pk.at(i - j) * T(j, n, q);
            }
            pk /= i;
            Pk.push_back(pk);
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
    size_t n = 50;
    nombre objectif = 0.02L;
    std::cout << std::fixed << std::setprecision(10);
    nombre limite = puissance_float(0.1, 11);
    nombre dq = 1;
    nombre q = 50;

    while (dq > limite) {
        // https://fr.wikipedia.org/wiki/Loi_Poisson_binomiale
        const nombre p = P(20, n, q + dq);
        if (p < objectif)
            dq /= 10.0;
        else
            q += dq;
    }

    return std::to_string(q, 10);
}
