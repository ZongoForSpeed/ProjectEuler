#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>
typedef boost::multiprecision::mpz_int nombre;

#include <boost/rational.hpp>
#include <boost/optional.hpp>

namespace
{
    nombre f(nombre n)
    {
        static std::map<nombre, nombre> cache;
        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;

        // f(n) = f(n/2) + f(n/2 - 1) si n pair
        // f(n) = f((n-1)/2) si n impair
        nombre resultat = 0;
        if (n == 0)
            resultat = 1;
        else if (n%2 == 0)
            resultat = f(n/2) + f(n/2 - 1);
        else
            resultat = f(n/2);
            
        cache[n] = resultat;
        return  resultat;
    }
}

void probleme169()
{
    Timer timer("probleme 169");
    // Define f(0)=1 and f(n) to be the number of different ways n can be expressed as a sum of integer powers of 2 using each power no more than twice.
    //
    // For example, f(10)=5 since there are five different ways to express 10:
    // 
    // 1 + 1 + 8
    // 1 + 1 + 4 + 4
    // 1 + 1 + 2 + 2 + 4
    // 2 + 4 + 4
    // 2 + 8
    // 
    // What is f(10^25)?
    nombre n = puissance::puissance<nombre>(10, 25);
    nombre resultat = f(n);
    std::cout << "Solution: " << resultat << std::endl;
}
