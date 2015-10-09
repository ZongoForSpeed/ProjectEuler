#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme190()
{
    Timer timer("probleme 190");
    // Let Sm = (x1, x2, ... , xm) be the m-tuple of positive real numbers with x1 + x2 + ... + xm = m 
    // for which Pm = x1 * x2² * ... * xm^m is maximised.
    //
    // For example, it can be verified that [P10] = 4112 ([ ] is the integer part function).
    //
    // Find Σ[Pm] for 2 ≤ m ≤ 15.
    nombre resultat = 0;
    for (nombre m = 2; m <= 15; ++m)
    {
        long double produit = 1;
        for (nombre i = 1; i <= m; ++i)
        {
            produit *= puissance::puissance(((long double)2*i)/(m+1), i);
        }
        resultat += std::floor(produit);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
