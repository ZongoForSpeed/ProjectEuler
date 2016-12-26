#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef unsigned long long nombre;

namespace
{
    bool premier(nombre n)
    {
        boost::multiprecision::mpz_int z = n;
        return premiers::test(z, 10);
    }
}

ENREGISTRER_PROBLEME(291, "Panaitopol Primes")
{
    // A prime number p is called a Panaitopol prime if (x**4 - y**4)/(x**3 + y**3)
    // for some positive integers x and y.
    //
    // Find how many Panaitopol primes are less than 5×10**15.
    const nombre limite = 5*puissance::puissance<nombre, unsigned>(10, 15);
    
    nombre resultat = 0;
    for (nombre n = 1; n*n + (n+1)*(n+1) < limite; ++n)
    {
        if (premier(n*n + (n+1)*(n+1)))
            ++resultat;
    }
    
    return std::to_string(resultat);
}
