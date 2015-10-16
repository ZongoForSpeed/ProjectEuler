#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"
#include "Graphe.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(110, "Diophantine reciprocals II")
{
    Timer t("probleme 110");
    // In the following equation x, y, and n are positive integers.
    // 
    //                                          1/x + 1/y = 1/n
    //
    // It can be verified that when n = 1260 there are 113 distinct solutions and this is the least 
    // value of n for which the total number of distinct solutions exceeds one hundred.
    // 
    // What is the least value of n for which the number of distinct solutions exceeds four million?
    // 
    // NOTE: This problem is a much more difficult version of Problem 108 and as it is well beyond 
    // the limitations of a brute force approach it requires a clever implementation.
    nombre limite = 4000000;
    
    vecteur premiers;
    premiers::crible23<nombre>(limite * 3, std::back_inserter(premiers));
    
    std::map<nombre, nombre> decomposition;
    for (nombre n = 2*limite + 1;; n += 2)
    {
        decomposition.clear();
        arithmetiques::decomposition(n, premiers, decomposition);
        
        vecteur facteur_premiers;
        for (const auto & d: decomposition)
            facteur_premiers.push_back(d.first);

        if (std::equal(premiers.begin() + 1, premiers.begin() + facteur_premiers.size() + 1, facteur_premiers.begin()))
            break;
    }

    vecteur exposants;
    for (const auto & d: decomposition)
        exposants.insert(exposants.end(), d.second, (d.first - 1) / 2);

    std::reverse(exposants.begin(), exposants.end());

    nombre resultat = 1;
    for (size_t n = 0; n < exposants.size(); ++n)
    {
        resultat *= puissance::puissance(premiers[n], exposants[n]);
    }

	std::cout << "Solution: " << resultat << std::endl;
}
