#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;

void probleme035()
{
    Timer t ("probleme 35");
    // The number, 197, is called a circular prime because all rotations of the digits: 
    // 197, 971, and 719, are themselves prime.
    // 
    // There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
    // 
    // How many circular primes are there below one million?
    std::set<nombre> premiers;
    premiers::crible(1000000, premiers);
    
    auto valide = [&premiers] (nombre n) -> bool
    {
        auto rotation = [](nombre n)
        {
            auto liste = arithmetiques::extraire_chiffres(n);
            liste.push_back(liste.front());
            liste.pop_front();
            nombre r = 0;
            for (const auto & c: liste)
                r = 10*r + c;
            return r;
        };
        
        auto chiffres = arithmetiques::extraire_chiffres(n);
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
    
    nombre resultat = 0;
    for (const auto p: premiers)
    {
        if (valide(p)) ++resultat;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}