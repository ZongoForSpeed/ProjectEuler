#include "problemes.h"
#include "premiers.h"

#include <iostream>
#include <numeric>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(10, "Summation of primes")
{
    // The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
    // 
    // Find the sum of all the primes below two million.
    vecteur premiers;
    premiers::crible<nombre>(2000000, std::back_inserter(premiers));
    nombre solution = std::accumulate(premiers.begin(), premiers.end(), nombre(0));
    std::cout << "Solution: " << solution << std::endl;
}