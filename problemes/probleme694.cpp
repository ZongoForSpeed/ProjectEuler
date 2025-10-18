#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"
#include "timer.h"

#include <set>

namespace {
    size_t s(size_t n, const std::vector<size_t> &premiers) {
        size_t d = 1;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                size_t compteur = 0;
                while (n % p == 0) {
                    n /= p;
                    ++compteur;
                }
                if (compteur >= 3) {
                    d *= compteur - 1;
                }
            }
        }

        return d;
    }

    size_t S(size_t n, const std::vector<size_t> &premiers) {
        size_t somme = 0;
        for (size_t i = 1; i <= n; ++i) {
            somme += s(i, premiers);
        }
        return somme;
    }
}

ENREGISTRER_PROBLEME(694, "Cube-full Divisors") {
    // A positive integer n is considered cube-full, if for every prime p that divides n, so does p^3. Note that 1 is
    // considered cube-full.
    //
    // Let s(n) be the function that counts the number of cube-full divisors of n. For example 1, 8 and 16 are the three
    // cube-full divisors of 16. Therefore, s(16) = 3.
    //
    // Let S(n) represent the summatory function of s(n), that is S(n) = Sum_{i=1..n} s(i).
    //
    // You are given S(16) = 19, S(100) = 126 and S(10000) = 13344.
    //
    // Find S(10^18).
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(1'000'000, std::back_inserter(premiers));

    std::cout << "s(16) = " << s(16, premiers) << std::endl;
    std::cout << "S(16) = " << S(16, premiers) << std::endl;
    std::cout << "S(100) = " << S(100, premiers) << std::endl;
    std::cout << "S(10000) = " << S(10000, premiers) << std::endl;

    auto limite = mpz_nombre::puissance(10, 18);

    std::set<mpz_nombre> cubes {1};
    for (size_t p: premiers) {
        std::vector<mpz_nombre> suivant;
        for (mpz_nombre f = p * p * p; f <= limite; f *= p) {
            for (const auto& e: cubes) {
                mpz_nombre n = f * e;
                if (n > limite) {
                    break;
                }
                suivant.emplace_back(n);
            }
        }

        cubes.insert(suivant.begin(), suivant.end());
        // std::cout << "p = " << p << ": " << facteurs.size() << std::endl;
    }

    mpz_nombre resultat = 0;
    for (auto& f: cubes) {
        resultat += limite / f;
    }

    return resultat.to_string();
}
