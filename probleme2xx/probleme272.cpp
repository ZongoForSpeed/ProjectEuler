#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "combinatoire.h"

#include <iostream>
#include <boost/multiprecision/gmp.hpp>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    
    template<typename Iterator>
    nombre algorithme(Iterator it, Iterator en, nombre limite, nombre m, nombre n)
    {
        if (m < 0) return 0;
        
        nombre total = 0;
        nombre n0 = n;
        while (true)
        {
            n = n0;
            if (it == en || n*it->first > limite)
            {
                if (m != 0)
                    break;
                
                total += n;
                break;
            }
            
            if (n*puissance::puissance(it->first, static_cast<size_t>(m)) > limite)
                break;
            nombre m2 = m;
            if (it->second == 3)
                --m2;
            while (it->first*n < limite)
            {
                n *= it->first;
                total += algorithme(it + 1, en, limite,m2,n);
                if (it->first == 3)
                {
                    --m2;
                    while (it->first*n < limite)  
                    {
                        n *= it->first;
                        total += algorithme(it + 1, en, limite, m2, n);
                    }
                    break;
                }
            }
            
            ++it;
        }
        
        return total;
    }
}

ENREGISTRER_PROBLEME(272, "Modular Cubes, part 2")
{
    // For a positive number n, define C(n) as the number of the integers x, for
    // which 1<x<n and x3≡1 mod n.
    //
    // When n=91, there are 8 possible values for x, namely : 9, 16, 22, 29, 53,
    // 74, 79, 81.
    // Thus, C(91)=8.
    //
    // Find the sum of the positive numbers n≤10**11 for which C(n)=242.
    const nombre limite = puissance::puissance<nombre>(10, 11);
    vecteur premiers;
    premiers::crible<nombre>(100000000, std::back_inserter(premiers));
    
    std::vector<std::pair<nombre, short>> premiers_cubiques;
    for (nombre p : premiers)
    {
        premiers_cubiques.push_back(std::make_pair(p, (p%3 == 1)?3:1));
    }
    
    nombre resultat = algorithme(premiers_cubiques.begin(), premiers_cubiques.end(), limite, 5, 1);
    return std::to_string(resultat);
}
