#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <map>

#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;

void probleme014()
{
    Timer t("probleme 14");
    // The following iterative sequence is defined for the set of positive integers:
    // 
    // n -> n/2 (n is even)
    // n -> 3n + 1 (n is odd)
    // 
    // Using the rule above and starting with 13, we generate the following sequence:
    // 
    // 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
    // It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. 
    // Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
    // 
    // Which starting number, under one million, produces the longest chain?
    // 
    // NOTE: Once the chain starts the terms are allowed to go above one million.
    std::map<nombre, nombre> cache;
    cache[1] = 1;
    
    nombre max_longueur = 1;
    nombre max_nombre = 1;
    for (nombre n = 2; n < 1000000; ++n)
    {
        std::vector<nombre> chaine;
        chaine.push_back(n);
        nombre p = n;
        while (cache.find(p) == cache.end())
        {
            if (p%2 == 0)
                p /= 2;
            else
                p = 3*p + 1;
            chaine.push_back(p);    
        }
        
        nombre longueur = cache[p];
        for (const nombre & c : boost::adaptors::reverse(chaine))
        {
            cache[c] = ++longueur;
        }
        
        if (cache[n] > max_longueur)
        {
            max_longueur = cache[n];
            max_nombre = n;
        }
    }
    
    std::cout << "Solution: " << max_nombre << std::endl;
}
