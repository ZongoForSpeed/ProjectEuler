#include "problemes.h"
#include "arithmetique.h"
#include "utilitaires.h"
#include "iterator.h"

#include <boost/rational.hpp>
#include <set>

typedef long long nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<fraction> vecteur;

namespace {
    std::set<fraction> algorithme(const vecteur &e, std::map<std::vector<fraction>, std::set<fraction>> &cache) {
        if (auto it = cache.find(e);it != cache.end())
            return it->second;

        std::set<fraction> resultat;

        fraction f = 0;
        for (auto d: e) f = f * 10 + d;
        resultat.insert(f);

        for (size_t n = 1; n < e.size(); ++n) {
            auto gauche = algorithme(vecteur(e.begin(), iterator::next(e.begin(), n)), cache);
            auto droite = algorithme(vecteur(iterator::next(e.begin(), n), e.end()), cache);

            for (auto a: gauche)
                for (auto b: droite) {
                    resultat.insert(a + b);
                    resultat.insert(a - b);
                    resultat.insert(a * b);
                    if (b != 0)
                        resultat.insert(a / b);
                }
        }

        cache.emplace(e, resultat);
        return resultat;
    }
}

ENREGISTRER_PROBLEME(259, "Reachable Numbers") {
    // A positive integer will be called reachable if it can result from an 
    // arithmetic expression obeying the following rules:
    //
    //      . Uses the digits 1 through 9, in that order and exactly once each.
    //      . Any successive digits can be concatenated (for example, using the 
    //      digits 2, 3 and 4 we obtain the number 234).
    //      . Only the four usual binary arithmetic operations (addition, 
    //      subtraction, multiplication and division) are allowed.
    //      . Each operation can be used any number of times, or not at all.
    //      . Unary minus is not allowed.
    //      . Any number of (possibly nested) parentheses may be used to define 
    //      the order of operations.
    // 
    // For example, 42 is reachable, since (1/23) * ((4*5)-6) * (78-9) = 42.
    //
    // What is the sum of all positive reachable integers?
    std::vector<fraction> e{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::map<std::vector<fraction>, std::set<fraction>> cache;
    auto resultat = algorithme(e, cache);
    nombre solution = 0;
    for (auto f: resultat) {
        if (f > 0 && f.denominator() == 1) {
            solution += f.numerator();
        }
    }

    return std::to_string(solution);
}
