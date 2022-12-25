#include "problemes.h"
#include "utilitaires.h"
#include "timer.h"
#include "mpf_nombre.h"

namespace {
    short parite(size_t n) {
        return n % 2 == 0 ? 1 : -1;
    }

    mpz_nombre Stirling(std::map<std::pair<size_t, size_t>, mpz_nombre> &cache, size_t n, size_t k) {
        if (auto it = cache.find(std::make_pair(n, k)); it != cache.end()) {
            return it->second;
        }
        // https://fr.wikipedia.org/wiki/Nombre_de_Stirling#Nombre_de_Stirling_de_seconde_esp%C3%A8ce
        mpz_nombre resultat = 0;
        for (size_t i = 0; i <= k; ++i) {
            resultat += parite(i)
                        * mpz_nombre::coefficient_binomial(k, i)
                        * mpz_nombre::puissance(k - i, n);
        }
        resultat /= mpz_nombre::factorielle(k);
        return cache[std::make_pair(n, k)] = resultat;
    }

    mpf_nombre Polylogarithm(std::map<std::pair<size_t, size_t>, mpz_nombre> &cache, size_t n, mpf_nombre z) {
        // https://en.wikipedia.org/wiki/Polylogarithm#Particular_values
        const mpf_nombre q = z / (1 - z);
        mpf_nombre resultat = 0;
        for (size_t k = 0; k <= n; ++k) {
            mpz_nombre ak = mpz_nombre::factorielle(k) * Stirling(cache, n + 1, k + 1);
            resultat += ak * std::pow(q, k + 1);
        }

        return resultat;
    }

    long double E(std::map<std::pair<size_t, size_t>, mpz_nombre> &cache, size_t k, mpf_nombre q) {
        double epsilon = std::numeric_limits<double>::epsilon();
        mpf_nombre resultat = 0;
        mpf_nombre qm = 1;
        for (size_t m = 1;; ++m) {
            qm *= q;
            mpf_nombre f = Polylogarithm(cache, k, qm);
            if (resultat * epsilon > f) {
                break;
            }

            resultat += f;
        }

        long double ldResultat = resultat.get_long_double();
        std::cout << "E(" << k << ", " << q << ") = " << std::to_scientific(ldResultat, 12) << std::endl;

        return ldResultat;
    }
}

ENREGISTRER_PROBLEME(722, "Slowly converging series") {
    // For a non-negative integer k, define
    //
    //  Ek(q) = Sum_n=1..∞ σk(n)q^n
    //
    // where σk(n) = Sum_d|n d^k is the sum of the k-th powers of the positive divisors of n.
    //
    // It can be shown that, for every k, the series Ek(q) converges for any 0 < q < 1.
    //
    // For example,
    //  E1(1 - 1/2^4) = 3.872155809243e2
    //  E3(1 - 1/2^8) = 2.767385314772e10
    //  E7(1 - 1/2^15) = 6.725803486744e39
    //
    // All the above values are given in scientific notation rounded to twelve digits after the decimal point.
    //
    // Find the value of E15(1 - 1/2^25).
    //
    // Give the answer in scientific notation rounded to twelve digits after the decimal point.
    mpf_nombre::setPrecision(256);

    std::map<std::pair<size_t, size_t>, mpz_nombre> cache;

    for (size_t n = 0; n <= 10; ++n) {
        std::cout << n << '\t';
        for (size_t k = 0; k <= n; ++k) {
            std::cout << Stirling(cache, n, k) << '\t';
        }
        std::cout << std::endl;
    }

    std::cout << Polylogarithm(cache, 3, 0.99609375) << std::endl;
    E(cache, 1, 1.0L - std::pow(0.5L, 4.0L));
    E(cache, 3, 1.0L - std::pow(0.5L, 8.0L));
    E(cache, 7, 1.0L - std::pow(0.5L, 15.0L));

    long double resultat = E(cache, 15, 1.0L - std::pow(0.5L, 25.0L));
    return std::to_scientific(resultat, 12);
}
