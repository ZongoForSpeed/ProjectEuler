#include "problemes.h"

#include <string>

#include "puissance.h"

typedef unsigned long long nombre;

namespace {
    bool test2025(nombre n) {
        for (size_t i = 1; i <= n; i *= 10) {
            nombre right = n % i;
            if (10 * right < i) {
                continue;
            }
            nombre left = n / i;
            nombre sum = left + right;
            if (sum * sum == n) {
                return true;
            }
        }
        return false;
    }

    nombre T(unsigned short d) {
        nombre result = 0;
        nombre limit = puissance::puissance<nombre>(10, d / 2);
        for (nombre n = 1; n < limit; ++n) {
            if (n % 9 < 2) {
                // Only looking at case n = 0 mod 9 or 1 mod 9
                nombre n2 = n * n;
                if (test2025(n2)) {
                    // std::cout << "n2 = " << n2<< std::endl;
                    result += n2;
                }
            }
        }
        return result;
    }
}

ENREGISTRER_PROBLEME(932, "2025") {
    // For the year 2025
    // 2025 = (20 + 25)^2
    // Given positive integers $a$ and $b$, the concatenation $ab$ we call a $2025$-number if $ab = (a+b)^2$.
    // Other examples are $3025$ and $81$.
    // Note $9801$ is not a $2025$-number because the concatenation of $98$ and $1$ is $981$.
    //
    // Let $T(n)$ be the sum of all $2025$-numbers with $n$ digits or less. You are given $T(4) = 5131$.
    //
    // Find $T(16)$.
    std::cout << "T(4) = " << T(4) << std::endl;
    nombre result = T(16);
    std::cout << "T(16) = " << result << std::endl;
    return std::to_string(result);
}
