#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <set>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(47, "Distinct primes factors")
{
    // The first two consecutive numbers to have two distinct prime factors are:
    //
    //              14 = 2 × 7
    //              15 = 3 × 5
    //
    // The first three consecutive numbers to have three distinct prime factors are:
    // 
    //              644 = 2² × 7 × 23
    //              645 = 3 × 5 × 43
    //              646 = 2 × 17 × 19.
    // 
    // Find the first four consecutive integers to have four distinct prime factors. 
    // What is the first of these numbers?
    std::set<nombre> premiers;
    premiers::crible<nombre>(1000000, std::inserter(premiers, premiers.begin()));
    nombre resultat = 0;
    
    std::list<std::vector<nombre>> decomposition;
    
    nombre n = 2;
    while (true)
    {
        {
            std::map<nombre, nombre> d;
            arithmetiques::decomposition(n, premiers, d);
            std::vector<nombre> f;
            for (const auto & i: d)
                f.push_back(puissance::puissance(i.first, i.second));
            decomposition.push_back(f);
        }
        if (decomposition.size() > 4)
            decomposition.pop_front();
        
        std::set<nombre> facteur;
        for (const auto & i: decomposition)
        {
            if (i.size() != 4)
                break;
            for (const auto & f: i)
                facteur.insert(f);
        }
        
        if (facteur.size() == 16)
        {
            resultat = n - 3;
            break;
        }
        
        ++n;
    }
    
    return std::to_string(resultat);
}
