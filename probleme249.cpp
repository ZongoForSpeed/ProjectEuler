#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(249, "Prime Subset Sums")
{
    // Let S = {2, 3, 5, ..., 4999} be the set of prime numbers less than 5000.
    //
    // Find the number of subsets of S, the sum of whose elements is a prime number.
    // Enter the rightmost 16 digits as your answer.
    nombre masque = puissance::puissance<nombre>(10, 16);
    
    vecteur premiers;
    premiers::crible<nombre>(5000, std::back_inserter(premiers));
    
    nombre somme = std::accumulate(premiers.begin(), premiers.end(), 0ULL);
    vecteur t(somme + 1, 0);
    t[0] = 1;
    
    nombre sp = 0;
    for (nombre p: premiers)
    {
        sp += p;
        for (size_t j = sp; j > p - 1; --j)
        {
            t[j] = (t[j] + t[j-p]) % masque;
        }
    }
    
    premiers.clear();
    premiers::crible<nombre>(somme, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for(nombre p: premiers)
    {
        resultat = (resultat + t[p]) % masque;
    }

    std::cout << "Solution: " << resultat << std::endl;
}
