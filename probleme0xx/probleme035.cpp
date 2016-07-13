#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"

#include <iostream>
#include <algorithm>
#include <set>

typedef unsigned long long nombre;

namespace
{
    nombre rotation(nombre n)
    {
        auto liste = chiffres::extraire_chiffres(n);
        liste.push_back(liste.front());
        liste.pop_front();
        nombre r = 0;
        for (const auto & c: liste)
            r = 10*r + c;
        return r;
    }
    
    bool valide(nombre n, const std::set<nombre> & premiers)
    {
        auto chiffres = chiffres::extraire_chiffres(n);
        if (std::count(chiffres.begin(), chiffres.end(), 0) != 0)
            return false;
        
        nombre tmp = n;
        bool valide = true;
        while (valide)
        {
            tmp = rotation(tmp);
            if (tmp == n)
                break;
            if (premiers.find(tmp) == premiers.end())
                valide = false;
        }
        return valide;
    };
}

ENREGISTRER_PROBLEME(35, "Circular primes")
{
    // The number, 197, is called a circular prime because all rotations of the digits: 
    // 197, 971, and 719, are themselves prime.
    // 
    // There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
    // 
    // How many circular primes are there below one million?
    std::set<nombre> premiers;
    premiers::crible<nombre>(1000000, std::inserter(premiers, premiers.begin()));
    
    
    nombre resultat = 0;
    for (const auto p: premiers)
    {
        if (valide(p, premiers)) ++resultat;
    }
    
    return std::to_string(resultat);
}
