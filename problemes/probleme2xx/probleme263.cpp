#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool pratique(nombre n, const vecteur &premiers) {
        // https://fr.wikipedia.org/wiki/Nombre_pratique
        // n > 1 est pratique si et seulement si sa décomposition en facteurs 
        // premiers s'écrit n=p_0^a_0.p_1^a_1...p_k^a_k
        // avec k ≥ 0, p0 < p1 < … < pk premiers, α0, … , αk > 0 et
        // Quelquesoit i dans {0, ... ,k} p_i <= 1+sigma(p_0^a_0.p_1^a_1...p_i-1^a_i-1)
        std::map<nombre, size_t> d;
        arithmetique::decomposition(n, premiers, d);
        nombre s = 1;
        for (auto &[pi, ei]: d) {
            nombre sigma = arithmetique::somme_diviseurs(s, premiers);
            if (pi > 1 + sigma)
                return false;
            s *= puissance::puissance(pi, ei);
        }

        return true;
    }
}

ENREGISTRER_PROBLEME(263, "An engineers' dream come true") {
    // Consider the number 6. The divisors of 6 are: 1,2,3 and 6.
    // Every number from 1 up to and including 6 can be written as a sum of distinct divisors of 6:
    //      1=1, 2=2, 3=1+2, 4=1+3, 5=2+3, 6=6.
    // A number n is called a practical number if every number from 1 up to and including n can be expressed as a sum of
    // distinct divisors of n.
    // 
    // A pair of consecutive prime numbers with a difference of six is called a sexy pair (since "sex" is the Latin word
    // for "six"). The first sexy pair is (23, 29).
    // 
    // We may occasionally find a triple-pair, which means three consecutive sexy prime pairs, such that the second
    // member of each pair is the first member of the next pair.
    // 
    // We shall call a number n such that :
    //      - (n-9, n-3), (n-3,n+3), (n+3, n+9) form a triple-pair, and
    //      - the numbers n-8, n-4, n, n+4 and n+8 are all practical,
    // an engineers’ paradise.
    //
    // Find the sum of the first four engineers’ paradises.
    vecteur premiers;
    premiers::crible235<nombre>(1200000000, std::back_inserter(premiers));

    nombre resultat = 0;
    nombre compteur = 0;
    for (size_t i = 0; i < premiers.size() - 3; ++i) {
        nombre p1 = premiers.at(i);
        if (premiers.at(i + 1) == p1 + 6
            && premiers.at(i + 2) == p1 + 12
            && premiers.at(i + 3) == p1 + 18) {
            nombre n = p1 + 9;
            if (pratique(n - 8, premiers)
                && pratique(n - 4, premiers)
                && pratique(n, premiers)
                && pratique(n + 4, premiers)
                && pratique(n + 8, premiers)) {
                resultat += n;
                ++compteur;
                if (compteur == 4)
                    break;
            }
        }
    }

    return std::to_string(resultat);
}
