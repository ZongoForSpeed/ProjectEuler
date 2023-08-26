#pragma once

#include "utilitaires.h"
#include "puissance.h"

namespace combinatoire {
    template<typename Nombre>
    constexpr Nombre coefficient_binomial(Nombre n, Nombre p) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n / 2)
            p = n - p;
        Nombre numerateur = 1;
        Nombre denominateur = 1;
        for (Nombre k = 0; k < p; ++k) {
            numerateur *= (n - k);
            denominateur *= (k + 1);
        }

        return numerateur / denominateur;
    }

    template<typename Nombre>
    constexpr Nombre coefficient_binomial(Nombre n, Nombre p, Nombre modulo) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n / 2)
            p = n - p;

        size_t numerateur = 1;
        size_t denominateur = 1;
        for (size_t i = 0; i < p; ++i) {
            numerateur = numerateur * (n - i) % modulo;
            denominateur = denominateur * (i + 1) % modulo;
        }
        return numerateur * puissance::puissance_modulaire<size_t>(denominateur, modulo - 2, modulo) % modulo;
    }

    template<typename Nombre>
    constexpr Nombre arrangement(Nombre n, Nombre p) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre resultat = 1;
        for (Nombre k = n - p + 1; k < n + 1; ++k) {
            resultat *= k;
        }

        return resultat;
    }

    template<typename Nombre>
    constexpr Nombre catalan(Nombre n) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        return coefficient_binomial<Nombre>(2 * n, n) / (n + 1);
    }

    template<typename Nombre>
    constexpr Nombre factorielle(Nombre n) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre resultat = 1;
        for (Nombre k = 2; k <= n; ++k) resultat *= k;
        return resultat;
    }
}
