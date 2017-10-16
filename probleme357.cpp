#include "problemes.h"
#include "premiers.h"

#include <vector>
#include <set>

typedef size_t nombre;

namespace {
    bool valide(nombre n, const std::set<nombre> &premiers) {
        for (nombre d = 2; d * d < n + 1; ++d) {
            if (n % d == 0) {
                if (n % (d * d) == 0)
                    return false;
                if (premiers.find(n / d + d) == premiers.end())
                    return false;
            }
        }
        return true;
    }
}

ENREGISTRER_PROBLEME(357, "Prime generating integers") {
    // Consider the divisors of 30: 1,2,3,5,6,10,15,30.
    // It can be seen that for every divisor d of 30, d+30/d is prime.
    // Find the sum of all positive integers n not exceeding 100 000 000 such that for every divisor d of n, d+n/d is
    // prime.
    nombre taille = 100000000L;
    std::set<nombre> premiers;

    premiers::crible2<nombre>(taille, std::inserter(premiers, premiers.begin()));

    nombre solution = 0;
    for (const nombre &p : premiers) {
        nombre n = p - 1;
        if (valide(n, premiers)) {
            solution += n;
        }
    }

    return std::to_string(solution);
}
