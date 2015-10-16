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

ENREGISTRER_PROBLEME(134)
{
    Timer t("probleme 134");
    // Consider the consecutive primes p1 = 19 and p2 = 23. It can be verified that 1219 is the smallest 
    // number such that the last digits are formed by p1 whilst also being divisible by p2.
    //
    // In fact, with the exception of p1 = 3 and p2 = 5, for every pair of consecutive primes, p2 > p1, 
    // there exist values of n for which the last digits are formed by p1 and n is divisible by p2. Let S 
    // be the smallest of these values of n.
    //
    // Find ∑ S for every pair of consecutive primes with 5 ≤ p1 ≤ 1000000.
    nombre limite = 1000000;
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));
    t.etape("fin crible");
    
    nombre dix = 10;
    
    nombre resultat = 0;
    for (nombre n = 0; n < premiers.size() - 1; ++n)
    {
        nombre p1 = premiers.at(n);
        nombre p2 = premiers.at(n + 1);
        if (p1 > 4 && p1 < limite)
        {
            nombre chiffres = chiffres::nombre_chiffres(p1);
            nombre b = puissance::puissance_modulaire(dix, chiffres * (p2 - 2), p2);
            b *= p2 - p1;
            b %= p2;
            resultat += b * puissance::puissance(dix, chiffres) + p1;
        }
    }
    std::cout << "Solution: " << resultat << std::endl;
}

