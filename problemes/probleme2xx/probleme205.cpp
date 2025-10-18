#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, nombre> dictionnaire;

namespace {
    dictionnaire fusion(const dictionnaire &d1, const dictionnaire &d2) {
        dictionnaire resultat;
        for (auto&[k1, v1]: d1) {
            for (auto&[k2, v2]: d2) {
                resultat[k1 + k2] += v1 * v2;
            }
        }
        return resultat;
    }

    dictionnaire fusion(const dictionnaire &d1, const vecteur &d2) {
        dictionnaire resultat;
        for (auto&[k1, v1]: d1) {
            for (auto de2: d2) {
                resultat[k1 + de2] += v1;
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(205, "Dice Game") {
    // Peter has nine four-sided (pyramidal) dice, each with faces numbered 1, 2, 3, 4.
    // Colin has six six-sided (cubic) dice, each with faces numbered 1, 2, 3, 4, 5, 6.
    //
    // Peter and Colin roll their dice and compare totals: the highest total wins. The result is a draw if the totals
    // are equal.
    //
    // What is the probability that Pyramidal Pete beats Cubic Colin? Give your answer rounded to seven decimal places
    // in the form 0.abcdefg
    vecteur D4{1, 2, 3, 4};
    vecteur D6{1, 2, 3, 4, 5, 6};

    const dictionnaire Zero{{0, 1}};

    auto Peter1 = fusion(Zero, D4);
    auto Peter2 = fusion(Peter1, Peter1);
    auto Peter4 = fusion(Peter2, Peter2);
    auto Peter8 = fusion(Peter4, Peter4);
    auto Peter9 = fusion(Peter8, Peter1);

    auto Colin1 = fusion(Zero, D6);
    auto Colin2 = fusion(Colin1, Colin1);
    auto Colin4 = fusion(Colin2, Colin2);
    auto Colin6 = fusion(Colin4, Colin2);

    nombre somme = 0;
    for (auto&[peter, p9]: Peter9) {
        for (auto&[colin, c6]: Colin6) {
            if (peter > colin)
                somme += p9 * c6;
        }
    }
    long double resultat = somme
                           / puissance::puissance<long double>(4, 9u)
                           / puissance::puissance<long double>(6, 6u);
    return std::to_fixed(resultat, 7);
}
