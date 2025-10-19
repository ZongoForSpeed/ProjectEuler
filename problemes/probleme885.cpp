#include "problemes.h"
#include "chiffres.h"
#include "mpz_nombre.h"
#include "puissance.h"

#include <deque>
#include <string>
#include <iostream>

namespace {
    unsigned long long f(const unsigned long long n) {
        auto c = chiffres::extraire_chiffres(n);
        std::ranges::sort(c);
        return chiffres::conversion_nombre<unsigned long long>(c.begin(), c.end());
    }

    unsigned long long S(unsigned short d) {
        // std::map<unsigned long long, unsigned long long> map;
        auto limit = puissance::puissance<unsigned long long>(10, d);
        unsigned long long result = 0;
        for (unsigned long long i = 1; i < limit; ++i) {
            unsigned long long i1 = f(i);
            // map[i1]++;
            result += i1;
        }
        // std::cout << map << std::endl;
        return result;
    }

    mpz_nombre count(const std::deque<unsigned short> &chiffres, unsigned short d, unsigned long long modulo) {
        mpz_nombre result(1);
        for (auto c: chiffres) {
            if (c > 0) {
                result *= mpz_nombre::coefficient_binomial(d, c);
                result %= modulo;
                d -= c;
            }
        }
        return result.get_unsigned_long_long();
    }

    unsigned long long f(const std::deque<unsigned short> &chiffres) {
        unsigned long long result = 0;
        for (unsigned short i = 0; i < chiffres.size(); ++i) {
            for (unsigned short d = 0; d < chiffres[i]; ++d) {
                result *= 10;
                result += i;
            }
        }
        return result;
    }

    unsigned long long loop(unsigned short d, unsigned long long modulo, std::deque<unsigned short> &c,
                            unsigned short chiffre, unsigned short r) {
        mpz_nombre result = 0;
        if (chiffre == 9) {
            c[chiffre] = d - r;
            // count
            result += f(c) * count(c, d, modulo);
            result %= modulo;
            c[chiffre] = 0;
        } else {
            for (unsigned short cd = 0; r + cd <= d; ++cd) {
                c[chiffre] = cd;
                result += loop(d, modulo, c, chiffre + 1, r + cd);
                result %= modulo;
                c[chiffre] = 0;
            }
        }
        return result.get_unsigned_long_long();
    }

    unsigned long long S(unsigned short d, unsigned long long modulo) {
        std::deque<unsigned short> c(10, 0);
        return loop(d, modulo, c, 0, 0);
    }
}

ENREGISTRER_PROBLEME(885, "A Bold Proposition") {
    // For a positive integer $d$, let $f(d)$ be the number created by sorting the digits of $d$ in ascending order,
    // removing any zeros. For example, $f(3403) = 334$.
    //
    // Let $S(n)$ be the sum of $f(d)$ for all positive integers $d$ of $n$ digits or less. You are given
    // $S(1) = 45$ and $S(5) = 1543545675$.
    //
    // Find $S(18)$. Give your answer modulo $1123455689$.
    std::cout << "f(3403) = " << f(3403) << std::endl;
    std::cout << "S(2) = " << S(2) << std::endl;
    std::cout << "S(5) = " << S(5) << std::endl;
    std::cout << "S(5) = " << S(5, 1'000'000'000'000ull) << std::endl;

    return std::to_string(S(18, 1123455689ull) );
}
