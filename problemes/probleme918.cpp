#include "problemes.h"

#include <iostream>

#include <string>

typedef long long nombre;

namespace {
    nombre a(std::map<nombre, nombre>& cache, nombre n) {
        if (auto it = cache.find(n);it != cache.end()) {
            return it->second;
        }

        nombre result = 0;
        if (n == 1) {
            result = 1;
        } else if (n % 2 == 0) {
            result = 2 * a(cache, n / 2);
        } else {
            result = a(cache, n / 2) - 3 * a(cache, n / 2 + 1);
        }

        cache[n] = result;
        return result;
    }

    nombre S(nombre n) {
        std::map<nombre, nombre> cache;
        return 4 * a(cache, 1) - a(cache, n / 2);
    }

}

ENREGISTRER_PROBLEME(918, "Recursive Sequence Summation") {
    // The sequence $a_n$ is defined by $a_1=1$, and then recursively for $n\geq1$:
    //                  a_{2n}   =   2a_n
    //                  a_{2n+1} =    a_n - 3a_{n+1}
    //
    // The first ten terms are $1, 2, -5, 4, 17, -10, -17, 8, -47, 34$.
    // Define S(N) = sum_{n=1}^N a_n$. You are given $S(10) = -13$.
    // Find $S(10^{12})$.
    std::map<nombre, nombre> cache;
    std::cout << "a(1) = " << a(cache, 1) << std::endl;
    std::cout << "a(2) = " << a(cache, 2) << std::endl;
    std::cout << "a(3) = " << a(cache, 3) << std::endl;
    std::cout << "a(4) = " << a(cache, 4) << std::endl;
    std::cout << "a(5) = " << a(cache, 5) << std::endl;
    std::cout << "a(6) = " << a(cache, 6) << std::endl;
    std::cout << "a(7) = " << a(cache, 7) << std::endl;
    std::cout << "a(8) = " << a(cache, 8) << std::endl;
    std::cout << "a(9) = " << a(cache, 9) << std::endl;
    std::cout << "a(10) = " << a(cache, 10) << std::endl;

    std::cout << "S(10) = " << S(10) << std::endl;

    nombre result = S(1'000'000'000'000) ;
    std::cout << "S(10^12) = " << result << std::endl;

    return std::to_string(result);
}
