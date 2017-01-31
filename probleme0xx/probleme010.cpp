#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"
#include "mp_nombre.h"

typedef std::vector<mp_nombre> vecteur;

ENREGISTRER_PROBLEME(10, "Summation of primes")
{
    // The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
    // 
    // Find the sum of all the primes below two million.
    vecteur premiers;
    premiers::crible2<mp_nombre>(2000000, std::back_inserter(premiers));
    mp_nombre solution = std::accumulate(premiers.begin(), premiers.end(), mp_nombre(0));
    return solution.to_string();
}
