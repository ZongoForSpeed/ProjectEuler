#include "premiers.h"
#include "problemes.h"

ENREGISTRER_PROBLEME(609, "π sequences") {
    // For every n≥1 the prime-counting function π(n) is equal to the number of primes not exceeding n.
    // E.g. π(6)=3 and π(100)=25.
    //
    // We say that a sequence of integers u=(u0,⋯,um) is a π sequence if
    //
    //      un ≥ 1 for every n
    //      un+1 = π(un)
    //      u has two or more elements
    //
    // For u0=10 there are three distinct π sequences: (10,4), (10,4,2) and (10,4,2,1).
    //
    // Let c(u) be the number of elements of u that are not prime
    // Let p(n,k) be the number of π sequences u for which u0≤n and c(u)=k.
    // Let P(n) be the product of all p(n,k) that are larger than 0.
    // You are given: P(10)=3×8×9×3=648 and P(100)=31038676032.
    //
    // Find P(10**8). Give your answer modulo 1000000007.
    size_t limite = 100'000'000;
    size_t modulo = 1000000007;
    std::vector<bool> premier;
    premiers::crible_simple(limite + 1, premier);

    std::vector<size_t> pi(limite + 1, 0);

    std::map<size_t, size_t> table;

    for (size_t i = 1; i < limite + 1; ++i) {
        pi[i] = pi[i - 1] + premier[i];

        size_t u = pi[i];
        size_t c = !premier[i];

        while (u > 0) {
            if (!premier[u]) {
                ++c;
            }
            table[c]++;
            u = pi[u];
        }
    }

    size_t resultat = 1;
    for (const auto &e: table) {
        resultat *= e.second % modulo;
        resultat %= modulo;
    }

    return std::to_string(resultat);
}
