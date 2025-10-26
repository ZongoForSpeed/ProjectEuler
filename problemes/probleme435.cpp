#include "problemes.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"

#include "mpz_nombre.h"

namespace {

    std::pair<mpz_nombre, mpz_nombre> fibonacci_(std::map<mpz_nombre, std::pair<mpz_nombre, mpz_nombre>> & cache, const mpz_nombre &n, const mpz_nombre &modulo) {
        if (n == 0)
            return std::make_pair(1, 0);

        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;

        auto [fk_1, fk] = fibonacci_(cache, n / 2, modulo);

        std::pair<mpz_nombre, mpz_nombre> resultat;

        if (n % 2 == 0)
            resultat = std::make_pair(fk * fk + fk_1 * fk_1, fk * (2 * fk_1 + fk));
        else
            resultat = std::make_pair(fk * (2 * fk_1 + fk), (fk_1 + fk) * (fk_1 + fk) + fk * fk);

        resultat.first %= modulo;
        resultat.second %= modulo;

        cache.emplace(n, resultat);
        return resultat;
    }

    mpz_nombre fibonacci(const mpz_nombre &n, const mpz_nombre &modulo) {
        std::map<mpz_nombre, std::pair<mpz_nombre, mpz_nombre>> cache;
        return fibonacci_(cache, n, modulo).second;
    }

    mpz_nombre F(const unsigned long long n, const unsigned x, const unsigned long long modulo) {
        // F_n(x)=(f_n*x^(n+2)+f_n+1*x^(n+1) − x) / (x²+x−1)
        mpz_nombre x2 = x*x + x - 1;
        mpz_nombre m2 = modulo * x2;
        mpz_nombre fn = fibonacci(n, m2);
        mpz_nombre fn1 = fibonacci(n + 1, m2);
        fn *= mpz_nombre::puissance_modulaire(x, n + 2, m2);
        fn %= m2;
        fn1 *= mpz_nombre::puissance_modulaire(x, n + 1, m2);
        fn1 %= m2;

        return ((fn + fn1 + m2 - x)%m2) / x2;

    }
}

ENREGISTRER_PROBLEME(435, "Polynomials of Fibonacci numbers") {
    // The Fibonacci numbers {fn, n ≥ 0} are defined recursively as fn = fn-1 + fn-2 with base cases f0 = 0 and f1 = 1.
    //
    // Define the polynomials {Fn, n ≥ 0} as Fn(x) = ∑fix^i for 0 ≤ i ≤ n.
    //
    // For example, F7(x) = x + x^2 + 2x^3 + 3x^4 + 5x^5 + 8x^6 + 13x^7, and F7(11) = 268357683.
    //
    // Let n = 1015. Find the sum [∑0≤x≤100 Fn(x)] mod 1307674368000 (= 15!).
    auto n = puissance::puissance<unsigned long long>(10, 15);
    unsigned long long modulo = 1307674368000;

    mpz_nombre resultat = 0;
    for (unsigned x = 1; x <= 100; ++x) {
        resultat += F(n, x, modulo);
        resultat %= modulo;
    }

    return std::to_string(resultat);
}
