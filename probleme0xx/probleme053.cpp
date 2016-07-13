#include "problemes.h"
#include "combinatoire.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

ENREGISTRER_PROBLEME(53, "Combinatoric selections")
{
    // There are exactly ten ways of selecting three from five, 12345:
    // 
    // 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
    // 
    // In combinatorics, we use the notation, 5C3 = 10.
    // 
    // In general,
    // 
    // nCr = n! / [r!(n−r)!] , where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
    // It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
    //
    // How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one-million?
    nombre compteur = 0;
    for (nombre n = 1; n <= 100; ++n)
    {
        for (nombre p = 0; p <= 100; ++p)
        {
            if (combinatoire::coefficient_binomial(n, p) > 1000000) ++compteur;
        }
    }
    
    return std::to_string(compteur);
}
