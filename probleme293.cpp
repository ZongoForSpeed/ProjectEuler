#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "timer.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre premier_suivant(nombre n)
    {
        boost::multiprecision::mpz_int z = n;
        boost::multiprecision::mpz_int premier;
        mpz_nextprime(premier.backend().data(), z.backend().data());
        
        return static_cast<nombre>(premier);  
    }
}

ENREGISTRER_PROBLEME(293, "Pseudo-Fortunate Numbers")
{
    // An even positive integer N will be called admissible, if it is a power of
    // 2 or its distinct prime factors are consecutive primes.
    // The first twelve admissible numbers are 2,4,6,8,12,16,18,24,30,32,36,48.
    //
    // If N is admissible, the smallest integer M > 1 such that N+M is prime,
    // will be called the pseudo-Fortunate number for N.
    //
    // For example, N=630 is admissible since it is even and its distinct prime
    // factors are the consecutive primes 2,3,5 and 7.
    // The next prime number after 631 is 641; hence, the pseudo-Fortunate number
    // for 630 is M=11.
    // It can also be seen that the pseudo-Fortunate number for 16 is 3.
    // 
    // Find the sum of all distinct pseudo-Fortunate numbers for admissible numbers
    // N less than 10**9.
    vecteur premiers;
    premiers::crible<nombre>(50, std::back_inserter(premiers));
    
    nombre limite = puissance::puissance<nombre>(10, 9);
    
    vecteur fortunate;
    for (nombre p = premiers.front(); p < limite; p *= premiers.front())
    {
        fortunate.push_back(p);
    }
    
    std::set<nombre> pseudoFortunate;
    for (const nombre & p: premiers)
    {
        vecteur suivant;
        for (nombre produit = p; produit < limite; produit *= p)
        {
            for (const nombre & n: fortunate)
            {
                nombre f = produit*n;
                if (f >= limite)
                    break;  
                suivant.push_back(f);
            }       
            std::sort(suivant.begin(), suivant.end());
        }
        
        if (suivant.size() == 0)
            break;
            
        for (const nombre & n: suivant)
        {
            nombre m = premier_suivant(n + 1) - n;
            pseudoFortunate.insert(m);
        }
            
        std::swap(fortunate, suivant);
    }

    nombre resultat = 0;
    for (const nombre & n: pseudoFortunate)
        resultat += n;
    
    std::cout << "Solution: " << resultat << std::endl;
}
