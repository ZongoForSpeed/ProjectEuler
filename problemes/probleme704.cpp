#include "problemes.h"
#include "combinatoire.h"
#include "chiffres.h"
#include "puissance.h"
#include "timer.h"

typedef unsigned long long nombre;

namespace {
    nombre g(nombre n, nombre m) {
        nombre c = combinatoire::coefficient_binomial_ull(n, m);
        nombre k = 0;
        while (c % 2 == 0) {
            ++k;
            c >>= 1u;
        }

        return k;
    }

    nombre F(nombre n) {
        size_t m = n + 1;
        size_t resultat = 0;
        for (size_t f = 2; f <= m; f *= 2) {
            resultat += (m % f != 0);
        }

        return resultat;
    }

    nombre S(nombre N) {
        // size_t resultat = 0;
        // for (size_t m = 2; m <= N + 1; ++m) {
        //     for (size_t f = 2; f <= m; f *= 2) {
        //         resultat += (m % f != 0);
        //     }
        // }
        //
        // return resultat;

        size_t L = N + 1;
        size_t resultat = 0;
        for (size_t f = 2; f < L; f *= 2) {
            resultat += L - (L / f + (f - 1));
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(704, "Eulercoin") {
    // Define g(n, m) to be the largest integer k such that 2^k divides (n, m). For example,
    // (12 5) = 792 = 2^3 x 3² x 11, hence g(12, 5).
    //
    // Then define F(n) = { max(g(n, m) : 0 <= m <= n }. F(10) = 3 and F(100) = 6.
    //
    // Let S(N) = Sum_n=1..N F(n). You are given that S(100) = 389 and S(10'000'000) = 203222840.
    //
    // Find S(10^16).
    std::cout << "g(12, 5) = " << g(12, 5) << std::endl;
    std::cout << "F(10) = " << F(10) << std::endl;
    std::cout << "F(100) = " << F(100) << std::endl;
    std::cout << "S(100) = " << S(100) << std::endl;
    std::cout << "S(10'000'000) = " << S(10'000'000) << std::endl;

    // for (size_t n = 0; n < 30; ++n) {
    //     std::cout << n << '\t';
    //     std::cout << std::string(30 - n, ' ');
    //     for (size_t p = 0; p <= n; ++p) {
    //         std::cout << g(n, p) << ' ';
    //     }
    //     nombre ligne = n;
    //     auto c = chiffres::extraire_chiffres(ligne, 2);
    //     std::cout << std::string(30 - n, ' ')
    //               << F(n) << " "
    //               << " ("
    //               << std::count(c.begin(), c.end(), 0) << ", "
    //               << std::count(c.begin(), c.end(), 1) << ')'
    //               << "\t" << c << std::endl;
    // }

    size_t resultat = S(puissance::puissance<size_t>(10, 16u));
    return std::to_string(resultat);
}
