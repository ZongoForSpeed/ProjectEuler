#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(176, "Right-angled triangles that share a cathetus")
{
    // The four right-angled triangles with sides (9,12,15), (12,16,20), (5,12,13) and (12,35,37) 
    // all have one of the shorter sides (catheti) equal to 12. It can be shown that no other integer
    // sided right-angled triangle exists with one of the catheti equal to 12.
    //
    // Find the smallest integer that can be the length of a cathetus of exactly 47547 different 
    // integer sided right-angled triangles.
    vecteur premiers;
    premiers::crible235<nombre>(1000000, std::back_inserter(premiers));
    // https://oeis.org/A046079
    // Let n = (2^a0)*(p1^a1)*...*(pk^ak).
    // Then a(n) = [(2*a0 - 1)*(2*a1 + 1)*(2*a2 + 1)*(2*a3 + 1)*...*(2*ak + 1) - 1]/2. 
    // Note that if there is no a0 term, i.e. if n is odd, then the first term is simply omitted.
    nombre objectif = 47547;
    
    std::map<nombre, nombre> decomposition;
    arithmetiques::decomposition(objectif * 2 + 1, premiers, decomposition);
    vecteur facteurs;
    for (auto p: decomposition)
        facteurs.push_back(p.first / 2);

    std::sort(facteurs.rbegin(), facteurs.rend());
    facteurs.front() += 1;
    
    nombre resultat = 1;
    for (nombre n = 0; n < facteurs.size(); ++n)
        resultat *= puissance::puissance(premiers[n], facteurs[n]);

    return std::to_string(resultat);
}
