#include <ranges>

#include "problemes.h"

#include <string>
#include <set>

#include "arithmetique.h"
#include "format/deque.h"
#include "premiers.h"
#include "puissance.h"
#include "timer.h"

typedef unsigned long long nombre;

namespace {

    nombre P(const nombre n, const nombre modulo = 1'234'567'891) {
        // M(n) = | 2 when n = 3
        //        | 1 when n > 3 and odd
        //        | F(n/2) when n === 0 mod 4
        //        | L(n/2) when n === 2 mod 4
        std::pair<nombre, nombre> fibonacci = std::make_pair(0, 1);
        std::pair<nombre, nombre> lucas = std::make_pair(2, 1);

        nombre result = 2;
        for (nombre k = 2; k <= n; k += 2) {
            auto [fn, fn1] = fibonacci;
            auto [ln, ln1] = lucas;
            result *= (k % 4 == 0) ? fn1 : ln1;
            result %= modulo;

            fibonacci = std::make_pair(fn1, (fn + fn1) % modulo);
            lucas = std::make_pair(ln1, (ln + ln1) % modulo);
        }

        return result;
    }

}


ENREGISTRER_PROBLEME(854, "Pisano Periods 2") {
    // For every positive integer $n$ the Fibonacci sequence modulo $n$ is periodic. The period depends on the value of $n$.
    // This period is called the <strong>Pisano period</strong> for $n$, often shortened to $\pi(n)$.
    //
    // Define $M(p)$ as the largest integer $n$ such that $\pi(n) = p$, and define $M(p) = 1$ if there is no such $n$.<br>
    // For example, there are three values of $n$ for which $\pi(n)$ equals $18$: $19, 38, 76$. Therefore $M(18) = 76$.
    //
    // Let the product function $P(n)$ be: $$P(n)=\prod_{p = 1}^{n}M(p).$$
    // You are given: $P(10)=264$.
    //
    // Find $P(1\,000\,000)\bmod 1\,234\,567\,891$.
    std::cout << "P(10) = " << P(10) << std::endl;

    mpz_nombre result = P(1'000'000);
    std::cout << "P(1'000'000) = " << result << std::endl;

    return std::to_string(result);
}
