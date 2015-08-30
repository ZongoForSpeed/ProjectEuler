#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <sstream>

typedef unsigned long long nombre;

void probleme037()
{
    Timer t("probleme 37");
    // The number 3797 has an interesting property. Being prime itself, it is possible to continuously
    // remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7.
    // Similarly we can work from right to left: 3797, 379, 37, and 3.
    //
    // Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
    //
    // NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
    std::set<nombre> premiers;
    premiers::crible<nombre>(1000000, std::inserter(premiers, premiers.begin()));
    nombre resultat = 0;
    for (nombre p: premiers)
    {
        nombre q = p;
        bool test = true;
        while (q != 0 && test)
        {
            test = premiers.find(q) != premiers.end();
            q /= 10;
        }
        q = 10;
        while (q < p && test)
        {
            test = premiers.find(p%q) != premiers.end();
            q *= 10;
        }
        if (test && p > 10)
            resultat += p;
    }

    std::cout << "Solution: " << resultat << std::endl;
}



