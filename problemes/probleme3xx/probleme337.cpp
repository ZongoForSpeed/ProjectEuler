#include <numeric>
#include "../problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "multidimension.h"
#include "timer.h"
#include "fenwick.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(337, "Totient Stairstep Sequences")
{
    // Let {a1, a2,..., an} be an integer sequence of length n such that:
    //
    // a1 = 6
    // for all 1 ≤ i < n : φ(ai) < φ(ai+1) < ai < ai+1
    // Let S(N) be the number of such sequences with an ≤ N.
    // For example, S(10) = 4: {6}, {6, 8}, {6, 8, 9} and {6, 10}.
    // We can verify that S(100) = 482073668 and S(10 000) mod 108 = 73808307.
    //
    // Find S(20 000 000) mod 108.
    //
    // φ denotes Euler's totient function.
    const nombre limite = 20'000'000;
    const nombre modulo = 100'000'000;
    
    std::vector<bool> crible(limite + 1, true);
    std::vector<size_t> phi(limite + 1, 0);
    std::iota(phi.begin(), phi.end(), 0ul);

    for (size_t i = 2; i < limite + 1; ++i) {
        if (crible[i]) {
            for (size_t j = i; j < limite + 1; j += i) {
                crible[j] = false;
                phi[j] /= i;
                phi[j] *= i-1;
            }
        }
    }
    
    Fenwick<nombre> fenwick(limite + 1);
    std::vector<nombre> f(limite + 1, 0);
    for (size_t n = limite; n > 5; --n) {
        size_t k = phi[n];
        // f[n] = (modulo + 1 + fenwick.somme(n-1, modulo) - fenwick.somme(k, modulo)) % modulo;
        f[n] = 1 + fenwick.range(k, n - 1, modulo);
        fenwick.add(k, f[n], modulo);
    }

    return std::to_string(f[6]);
}
