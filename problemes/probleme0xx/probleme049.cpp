#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(49, "Prime permutations") {
    // The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, 
    // is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit 
    // numbers are permutations of one another.
    //
    // There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting 
    // this property, but there is one other 4-digit increasing sequence.
    // 
    // What 12-digit number do you form by concatenating the three terms in this sequence?
    nombre limite = 10000;

    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));

    std::vector<vecteur> suites_premiers;
    for (size_t i = 0; i < premiers.size(); ++i) {
        nombre p = premiers.at(i);
        vecteur suite{p};
        if (p > 1000) {
            auto chiffres = chiffres::extraire_chiffres<nombre>(p);
            for (size_t j = i + 1; j < premiers.size(); ++j) {
                nombre q = premiers.at(j);
                if (std::is_permutation(chiffres.begin(), chiffres.end(),
                                        chiffres::extraire_chiffres<nombre>(q).begin())) {
                    suite.push_back(q);
                }
            }
        }

        if (suite.size() > 2)
            suites_premiers.push_back(suite);
    }

    vecteur resultat;
    for (const auto &s: suites_premiers) {
        if (s.size() == 3
            && (s[2] - s[1]) == (s[1] - s[0])) {
            resultat = s;
        }
    }

    return std::to_string(chiffres::conversion_nombre<nombre>(resultat.begin(), resultat.end(), 10000));
}
