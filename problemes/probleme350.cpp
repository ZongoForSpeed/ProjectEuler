#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"

namespace {
    uint128_t compteur_solution(size_t i, uint128_t n, uint128_t modulo, const std::vector<size_t> &premiers) {
        std::map<size_t, size_t> factorization;
        arithmetique::decomposition(i, premiers, factorization);

        uint128_t resultat = 1;
        for (auto[p, e]: factorization) {
            uint128_t g =
                    puissance::puissance_modulaire<uint128_t>(e + 1, n, modulo)
                    + puissance::puissance_modulaire<uint128_t>(e - 1, n, modulo)
                    + 2 * modulo
                    - 2 * puissance::puissance_modulaire<uint128_t>(e, n, modulo);
            resultat *= g;
            resultat %= modulo;
        }

        return resultat;
    }

    uint128_t f(size_t G, size_t L, uint128_t N, uint128_t modulo, const std::vector<size_t> &premiers) {
        size_t c = L / G;
        uint128_t resultat = 0;
        for (size_t i = 1; i <= c; ++i) {
            resultat += compteur_solution(i, N, modulo, premiers) * (L / i - G + 1);
            resultat %= modulo;
        }

        std::cout << "f(" << G << ", " << L << ", " << N << ") = " << resultat << std::endl;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(350, "Constraining the least greatest and the greatest least") {
    // A list of size n is a sequence of n natural numbers.
    // Examples are (2,4,6), (2,6,4), (10,6,15,6), and (11).
    //
    // The greatest common divisor, or gcd, of a list is the largest natural number that divides all entries of the list.
    // Examples: gcd(2,6,4) = 2, gcd(10,6,15,6) = 1 and gcd(11) = 11.
    //
    // The least common multiple, or lcm, of a list is the smallest natural number divisible by each entry of the list.
    // Examples: lcm(2,6,4) = 12, lcm(10,6,15,6) = 30 and lcm(11) = 11.
    //
    // Let f(G, L, N) be the number of lists of size N with gcd ≥ G and lcm ≤ L. For example:
    //
    // f(10, 100, 1) = 91.
    // f(10, 100, 2) = 327.
    // f(10, 100, 3) = 1135.
    // f(10, 100, 1000) mod 101^4 = 3286053.
    //
    // Find f(106, 1012, 1018) mod 101^4.
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(10'000'000, std::back_inserter(premiers));

    size_t modulo = puissance::puissance<size_t>(101, 4);
    f(10, 100, 1, modulo, premiers);
    f(10, 100, 2, modulo, premiers);
    f(10, 100, 3, modulo, premiers);
    f(10, 100, 1000, modulo, premiers);

    uint128_t solution = f(1'000'000, 1'000'000'000'000, 1'000'000'000'000'000'000, modulo, premiers);
    return std::to_string(solution);
}
