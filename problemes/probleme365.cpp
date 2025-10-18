#include "problemes.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"
#include "premiers.h"

#include "nombre_modulaire.h"

ENREGISTRER_PROBLEME(365, "A huge binomial coefficient") {
    // The binomial coefficient (10^18 10^9) is a number with more than 9 billion (9 x 10^9) digits.
    //
    //Let M(n, k, m) denote the binomial coefficient (n k) modulo m.
    //
    // Calculate Sum M(10^18, 10^9, p.q.r) for 1000 < p < q < r < 5000 and p, q, r prime
    size_t n = 1'000'000'000'000'000'000ull;
    size_t k = 1'000'000'000ull;
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(5000, std::back_inserter(premiers));


    std::map<size_t, size_t> binomial;

    for (auto it = std::upper_bound(premiers.begin(), premiers.end(), 1000),
                 en = std::upper_bound(premiers.begin(), premiers.end(), 5000);
         it != en; ++it) {
        size_t p = *it;
        nombre_modulaire Cnk = nombre_modulaire::coefficient_binomial(p, n, k);
        binomial[p] = Cnk.value();
    }

    unsigned long long resultat = 0;
    for (auto it1 = binomial.begin(), en1 = binomial.end(); it1 != en1; ++it1) {
        auto[p, rp] = *it1;
        for (auto it2 = std::next(it1); it2 != en1; ++it2) {
            auto[q, rq] = *it2;
            for (auto it3 = std::next(it2); it3 != en1; ++it3) {
                auto[r, rr] = *it3;
                if (rp == 0 && rq == 0 && rr == 0) {
                    continue;
                }
                std::vector modulos{p, q, r};
                std::vector restes{rp, rq, rr};
                auto M = arithmetique_modulaire::restes_chinois<size_t>(modulos, restes, premiers);
                // std::cout << modulos << " " << restes << " = " << M << std::endl;
                resultat += M;
            }
        }

    }

    return std::to_string(resultat);
}
