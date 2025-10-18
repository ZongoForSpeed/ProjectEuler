#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "timer.h"

#include <execution>

typedef std::vector<unsigned long long> vecteur;

ENREGISTRER_PROBLEME(221, "Alexandrian Integers") {
    // We shall call a positive integer A an "Alexandrian integer", if there exist integers p, q, r such that:
    //
    //      A = p · q · r       and        1/A = 1/p + 1/q + 1/r
    //
    // For example, 630 is an Alexandrian integer (p = 5, q = −7, r = −18). In fact, 630 is the 6th Alexandrian integer,
    // the first 6 Alexandrian integers being: 6, 42, 120, 156, 420 and 630.
    //
    // Find the 150000th Alexandrian integer.
    size_t limite = 150000;
    vecteur premiers;
    {
        Timer timer_crible("crible");
        premiers::crible235<unsigned long long>(1000000000ULL, std::back_inserter(premiers));
    }

    std::vector<mpz_nombre> alexandrian;
    for (unsigned long long p = 1; p < limite * 2 / 3; ++p) {
        mpz_nombre pp = p * p + 1;
        const auto diviseurs = arithmetique::diviseurs<mpz_nombre>(pp, premiers);
        for (size_t n = 0; 2 * n < diviseurs.size(); ++n) {
            auto d = diviseurs[n];
            alexandrian.emplace_back(p * (p + d) * (p + pp / d));
        }
    }

    std::ranges::sort(alexandrian);
    return alexandrian[limite - 1].to_string();
}
