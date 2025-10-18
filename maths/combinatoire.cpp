#include "combinatoire.h"

#include "puissance.h"

namespace {
    template<typename Nombre>
    Nombre internal_coefficient_binomial(Nombre n, Nombre p) {
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
    Nombre internal_coefficient_binomial(Nombre n, Nombre p, Nombre modulo) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n / 2)
            p = n - p;

        Nombre numerateur = 1;
        Nombre denominateur = 1;
        for (size_t i = 0; i < p; ++i) {
            numerateur = numerateur * (n - i) % modulo;
            denominateur = denominateur * (i + 1) % modulo;
        }
        return numerateur * puissance::puissance_modulaire<Nombre>(denominateur, modulo - 2, modulo) % modulo;
    }

    template<typename Nombre>
    Nombre internal_arrangement(Nombre n, Nombre p) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre resultat = 1;
        for (Nombre k = n - p + 1; k < n + 1; ++k) {
            resultat *= k;
        }

        return resultat;
    }

    template<typename Nombre>
    Nombre internal_catalan(Nombre n) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        return internal_coefficient_binomial<Nombre>(2 * n, n) / (n + 1);
    }

    template<typename Nombre>
    Nombre internal_factorielle(Nombre n) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre resultat = 1;
        for (Nombre k = 2; k <= n; ++k) resultat *= k;
        return resultat;
    }
}

namespace combinatoire {
    unsigned int coefficient_binomial_u(unsigned int n, unsigned int p) {
        return internal_coefficient_binomial(n, p);
    }

    unsigned long coefficient_binomial_ul(unsigned long n, unsigned long p) {
        return internal_coefficient_binomial(n, p);
    }

    unsigned long long coefficient_binomial_ull(unsigned long long n, unsigned long long p) {
        return internal_coefficient_binomial(n, p);
    }

    unsigned int coefficient_binomial_u(unsigned int n, unsigned int p, unsigned int modulo) {
        return internal_coefficient_binomial(n, p, modulo);
    }

    unsigned long coefficient_binomial_ul(unsigned long n, unsigned long p, unsigned long modulo) {
        return internal_coefficient_binomial(n, p, modulo);
    }

    unsigned long long coefficient_binomial_ull(unsigned long long n, unsigned long long p, unsigned long long modulo) {
        return internal_coefficient_binomial(n, p, modulo);
    }

    unsigned int arrangement_u(unsigned int n, unsigned int p) {
        return internal_arrangement<>(n, p);
    }

    unsigned long arrangement_ul(unsigned long n, unsigned long p) {
        return internal_arrangement<>(n, p);
    }

    unsigned long long arrangement_ull(unsigned long long n, unsigned long long p) {
        return internal_arrangement<>(n, p);
    }

    unsigned int catalan_u(unsigned int n) {
        return internal_catalan<>(n);
    }

    unsigned long catalan_ul(unsigned long n) {
        return internal_catalan<>(n);
    }

    unsigned long long catalan_ull(unsigned long long n) {
        return internal_catalan<>(n);
    }

    unsigned int factorielle_u(unsigned int n) {
        return internal_factorielle<>(n);
    }

    unsigned long factorielle_ul(unsigned long n) {
        return internal_factorielle<>(n);
    }

    unsigned long long factorielle_ull(unsigned long long n) {
        return internal_factorielle<>(n);
    }

}
