#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"

#include <execution>
#include <fstream>
#include <set>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    std::set<vecteur> test(const std::set<nombre> &premiers,
                           vecteur::const_iterator debut,
                           vecteur::const_iterator fin) {
        std::set<vecteur> resultat;
        if (auto p = chiffres::conversion_nombre<nombre>(debut, fin);premiers.find(p) != premiers.end())
            resultat.emplace(1, p);

        for (auto it = std::next(debut); it != fin; ++it) {
            if (auto p = chiffres::conversion_nombre<nombre>(debut, it);premiers.find(p) != premiers.end()) {
                if (std::set<vecteur> s = test(premiers, it, fin); !s.empty()) {
                    for (vecteur v: s) {
                        v.push_back(p);
                        std::sort(std::execution::par, v.begin(), v.end());
                        resultat.insert(v);
                    }
                }
            }
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(118, "Pandigital prime sets") {
    // Using all of the digits 1 through 9 and concatenating them freely to form decimal integers, 
    // different sets can be formed. Interestingly with the set {2,5,47,89,631}, all of the elements 
    // belonging to it are prime.
    //
    // How many distinct sets containing each of the digits one through nine exactly once contain 
    // only prime elements?
    std::set<nombre> premiers;
    premiers::crible23<nombre>(1000000000, std::inserter(premiers, premiers.begin()));

    std::set<vecteur> resultat;

    std::vector<nombre> chiffres{1, 2, 3, 4, 5, 6, 7, 8, 9};
    do {
        auto s = test(premiers, chiffres.begin(), chiffres.end());
        resultat.insert(s.begin(), s.end());
    } while (std::ranges::next_permutation(chiffres).found);

    return std::to_string(resultat.size());
}
