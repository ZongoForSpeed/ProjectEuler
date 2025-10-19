#include <iostream>

#include "problemes.h"
#include "premiers.h"
#include "timer.h"
#include "mpz_nombre.h"

namespace {
    mpz_nombre S(size_t k) {
        size_t n = k / 9;
        size_t r = k % 9 + 2;

        return (((r - 1) * r + 10) * mpz_nombre::puissance(10, n) - 2 * (r + 9 * n + 4)) / 2;
    }

    mpz_nombre S(size_t k, size_t modulo) {
        // std::cout << "S(" << k << ", " << modulo << ") = ..." << std::endl;
        size_t n = k / 9;
        size_t r = k % 9 + 2;
        // std::cout << "n = " << n << ", r = " << r << std::endl;

        mpz_nombre i = 2 * modulo - (2 * (r + 9 * n + 4) % modulo);
        // std::cout << "i = " << i << std::endl;

        // 2^-1 = 2^(phi(n) - 1) = 2^(n - 2)
        auto inverse_deux = mpz_nombre::puissance_modulaire(2, modulo - 2, modulo);
        // std::cout << "inverse_deux = " << inverse_deux << std::endl;
        return ((((r - 1) * r + 10) * mpz_nombre::puissance_modulaire(10, n, modulo) + i) *
                inverse_deux) % modulo;
    }
}

ENREGISTRER_PROBLEME(684, "Inverse Digit Sum") {
    // Define s(n) to be the smallest number that has a digit sum of n. For example s(10) = 19.
    // Let S(k) = Sum_{n=1..k} s(n). You are given S(20) = 1074.
    //
    // Further let fi be the Fibonacci sequence defined by f0 = 0, f1 = 1 and fi = fi-2 + fi-1 for all i >= 2
    //
    // Find Sum_{i=2..90} S(fi). Give your answer modulo 1 000 000 007.
    //
    const size_t modulo = 1'000'000'007;

    std::cout << "S(20) = " << S(20) << std::endl;
    std::cout << "S(49) = " << S(49) << std::endl;

    std::cout << "S(20) = " << S(20, modulo) << std::endl;
    std::cout << "S(49) = " << S(49, modulo) << std::endl;

    std::vector<size_t> fibonacci(91);
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    mpz_nombre resultat = 0;
    for (size_t i = 2; i <= 90; ++i) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        size_t fi = fibonacci[i];
        mpz_nombre Si = S(fi, modulo);
        std::cout << "S(" << fi << ") = " << Si << std::endl;
        resultat += Si;
        resultat %= modulo;
    }

    return resultat.to_string();
}
