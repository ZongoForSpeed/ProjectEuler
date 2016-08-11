#include "problemes.h"
#include "arithmetiques.h"

#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, nombre> dictionnaire;

namespace
{
    dictionnaire fusion(const dictionnaire & d1, const dictionnaire & d2)
    {
        dictionnaire resultat;
        for (auto de1: d1)
        for (auto de2: d2)
        {
            resultat[de1.first + de2.first] += de1.second * de2.second;
        }
        
        return resultat;
    }
    
    dictionnaire fusion(const dictionnaire & d1, const vecteur & d2)
    {
        dictionnaire resultat;
        for (auto de1: d1)
        for (auto de2: d2)
        {
            resultat[de1.first + de2] += de1.second;
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(205, "Dice Game")
{
    // Peter has nine four-sided (pyramidal) dice, each with faces numbered 1, 2, 3, 4.
    // Colin has six six-sided (cubic) dice, each with faces numbered 1, 2, 3, 4, 5, 6.
    //
    // Peter and Colin roll their dice and compare totals: the highest total wins. The result is a 
    // draw if the totals are equal.
    //
    // What is the probability that Pyramidal Pete beats Cubic Colin? Give your answer rounded to 
    // seven decimal places in the form 0.abcdefg
    vecteur D4 { 1, 2, 3, 4 };
    vecteur D6 { 1, 2, 3, 4, 5, 6 };
    
    const std::map<nombre, nombre> Zero {{ 0, 1 }};
    
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
    for (auto p: Peter9)
    for (auto c: Colin6)
    {
        if (p.first > c.first)
            somme += p.second * c.second;
    }
    
    long double resultat = somme / puissance::puissance(4.0L, 9) / puissance::puissance(6.0L, 6);
    return std::to_string(resultat, 7);
}
