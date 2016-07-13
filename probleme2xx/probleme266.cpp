#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(266, "Pseudo Square Root")
{
    // The divisors of 12 are: 1,2,3,4,6 and 12.
    // 
    // The largest divisor of 12 that does not exceed the square root of 12 is 3.
    // We shall call the largest divisor of an integer n that does not exceed 
    // the square root of n the pseudo square root (PSR) of n.
    // It can be seen that PSR(3102)=47.
    //
    // Let p be the product of the primes below 190.
    // Find PSR(p) mod 10^16.
    const nombre modulo = puissance::puissance<nombre>(10, 16);
    vecteur premiers;
    premiers::crible<nombre>(190, std::back_inserter(premiers));
    
    nombre p1 = 1;
    for (size_t n = 0; n < premiers.size() / 2; ++n)
        p1 *= premiers[n];
    auto d1 = arithmetiques::diviseurs(p1, premiers);
    
    nombre p2 = 1;
    for (size_t n = premiers.size() / 2; n < premiers.size(); ++n)
        p2 *= premiers[n];
    auto d2 = arithmetiques::diviseurs(p2, premiers);
    
    nombre resultat = 0;
    
    auto it1 = d1.begin();
    auto it2 = d2.rbegin();
    while (it1 != d1.end() && it2 != d2.rend())
    {
        nombre courant = (*it1) * (*it2);
        if (courant * courant > p1 * p2)
            ++it2;
        else
        {
            resultat = std::max(resultat, courant);
            ++it1;
        }
    }
    
    return std::to_string(resultat%modulo);
}
