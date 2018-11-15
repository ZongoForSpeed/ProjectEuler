#include "problemes.h"
#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"
#include "timer.h"

#include <fstream>

typedef std::vector<uint128_t> vecteur;

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
        premiers::crible235<uint128_t>(1000000000ULL, std::back_inserter(premiers));
    }

    vecteur Alexandrian;
    for (uint128_t p = 1; p < limite * 2 / 3; ++p) {
        uint128_t pp = p * p + 1;
        const auto diviseurs = arithmetique::diviseurs<uint128_t>(pp, premiers);
        for (size_t n = 0; 2 * n < diviseurs.size(); ++n) {
            auto d = diviseurs[n];
            uint128_t A = p * (p + d) * (p + pp / d);
            Alexandrian.push_back(A);
        }
    }

    std::sort(Alexandrian.begin(), Alexandrian.end());

    uint128_t resultat = Alexandrian[limite - 1];
    return std::to_string(resultat);
}
