#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "mp_nombre.h"

#include <fstream>

typedef std::vector<mp_nombre> vecteur;

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
        premiers::crible235<mp_nombre>(1000000000ULL, std::back_inserter(premiers));
    }

    vecteur Alexandrian;
    for (mp_nombre p = 1; p < limite * 2 / 3; ++p) {
        mp_nombre pp = p * p + 1;
        const auto diviseurs = arithmetiques::diviseurs<mp_nombre>(pp, premiers);
        for (size_t n = 0; 2 * n < diviseurs.size(); ++n) {
            auto d = diviseurs[n];
            mp_nombre A = p * (p + d) * (p + pp / d);
            Alexandrian.push_back(A);
        }
    }

    std::sort(Alexandrian.begin(), Alexandrian.end());

    mp_nombre resultat = Alexandrian[limite - 1];
    return resultat.to_string();
}