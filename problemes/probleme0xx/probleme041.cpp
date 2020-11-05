#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(41, "Pandigital prime") {
    // We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once.
    // For example, 2143 is a 4-digit pandigital and is also prime.
    //
    // What is the largest n-digit pandigital prime that exists?
    std::deque<nombre> premiers;
    premiers::crible2<nombre>(100000000, std::back_inserter(premiers));
    nombre resultat = 0;
    std::vector<nombre> pandigital{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (nombre p: premiers) {
        if (auto chiffres = chiffres::extraire_chiffres(p);
                std::is_permutation(chiffres.begin(), chiffres.end(), pandigital.begin()))
            resultat = p;
    }
    return std::to_string(resultat);
}
