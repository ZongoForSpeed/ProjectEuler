#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool premier(nombre n)
    {
        boost::multiprecision::mpz_int m(n);
        return mpz_probab_prime_p(m.backend().data(), 25) != 0;
    }
}

ENREGISTRER_PROBLEME(216, "Investigating the primality of numbers of the form 2n²-1")
{
    // Consider numbers t(n) of the form t(n) = 2n²-1 with n > 1.
    // The first such numbers are 7, 17, 31, 49, 71, 97, 127 and 161.
    // It turns out that only 49 = 7*7 and 161 = 7*23 are not prime.
    // For n ≤ 10000 there are 2202 numbers t(n) that are prime.
    // 
    // How many numbers t(n) are prime for n ≤ 50,000,000 ?
    nombre limite = 50000000;
    nombre resultat = 0;
    for (nombre n = 1; n <= limite; ++n)
    {
        if (premier(2*n*n-1))
            ++resultat;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
