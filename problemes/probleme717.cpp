#include "problemes.h"
#include "premiers.h"
#include "puissance.h"
#include "timer.h"

namespace {
    // ⌊ 2^2^p / p ⌋ mod 2^p = ?
    //  <=> 2^2^p ≡ x mod (2^p * p)     ⌊x/p⌋ = ?
    //  <=> 2^p * 2^(2^p - p) ≡ x mod (2^p * p)
    //      2^(2^p - p) ≡ y mod p
    //   => 2^p - p ≡ R mod p-1
    //  <=> 2^p - 1 ≡ R mod p-1
    //
    // f(p) = [(2^R mod p) * 2^p] / p
    //
    // g(p) = f(p) mod p
    //      = ⌊ [(2^R mod p) * 2^p] / p ⌋ / p
    //      = ⌊ [(2^R mod p) * 2^p] % p² ⌋ / p
    //      = { [(2^R mod p) * 2^p] % p² } / p
    unsigned long long R(size_t p) {
        // 2^p - 1 ≡ R mod p-1
        auto R = puissance::puissance_modulaire<unsigned long long>(2u, p, p - 1);
        R += p - 2;
        R %= p - 1;
        // 2^R mod p
        return puissance::puissance_modulaire<unsigned long long>(2u, R, p);
    }

    mpz_nombre f(size_t p) {
        mpz_nombre deux_p = mpz_nombre(2) << p;
        return (R(p) * deux_p) / p;
    }

    mpz_nombre g(size_t p) {
        mpz_nombre resultat = R(p);
        resultat *= puissance::puissance_modulaire<unsigned long long>(2u, p, p * p);
        resultat %= p * p;
        resultat /= p;
        return resultat;
    }

    mpz_nombre G(size_t N, const std::vector<size_t> &premiers) {
        mpz_nombre resultat = 0;
        const auto en = std::ranges::lower_bound(premiers, N);
        for (auto it = std::next(premiers.begin()); it != en; ++it) {
            resultat += g(*it);
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(717, "Summation of a Modular Formula") {
    // For an odd prime p, define f(p) = |2^(2^p) / p| mod 2^p
    // For example, when p=3, |2^8/3| = 85 ≡ 5 (mod 8) and so $f(3) = 5.
    //
    // Further define g(p) = f(p) mod p. You are given g(31) = 17.
    //
    // Now define G(N) to be the summation of g(p) for all odd primes less than N.
    //
    // You are given G(100) = 474 and G(10^4) = 2819236.
    //
    // Find G(10^7)
    size_t limite = 10'000'000;
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite, std::back_inserter(premiers));

    std::cout << "f(3) = " << f(3) << std::endl;
    std::cout << "g(3) = " << g(3) << std::endl;
    std::cout << "g(31) = " << g(31) << std::endl;
    std::cout << "G(100) = " << G(100, premiers) << std::endl;
    std::cout << "G(10'000) = " << G(10'000, premiers) << std::endl;

    mpz_nombre resultat = G(limite, premiers);
    std::cout << "G(10'000'000) = " << resultat << std::endl;
    return resultat.to_string();
}
