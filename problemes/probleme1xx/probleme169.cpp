#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"

namespace {
    size_t f(std::map<uint128_t, size_t> &cache, uint128_t n) {
        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;

        // f(n) = f(n/2) + f(n/2 - 1) si n pair
        // f(n) = f((n-1)/2) si n impair
        size_t resultat = 0;
        if (n == 0)
            resultat = 1;
        else if (n % 2 == 0)
            resultat = f(cache, n / 2) + f(cache, n / 2 - 1);
        else
            resultat = f(cache, n / 2);

        cache[n] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(169, "Exploring the number of different ways a number can be expressed as a sum of powers of 2") {
    // Define f(0)=1 and f(n) to be the number of different ways n can be expressed as a sum of integer powers of 2
    // using each power no more than twice.
    //
    // For example, f(10)=5 since there are five different ways to express 10:
    // 
    // 1 + 1 + 8
    // 1 + 1 + 4 + 4
    // 1 + 1 + 2 + 2 + 4
    // 2 + 4 + 4
    // 2 + 8
    // 
    // What is f(10^25)?
    uint128_t n = puissance::puissance<uint128_t>(10, 25);
    std::map<uint128_t, size_t> cache;
    size_t resultat = f(cache, n);
    return std::to_string(resultat);
}
