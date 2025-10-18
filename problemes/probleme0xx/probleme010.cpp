#include <numeric>
#include "numerique.h"
#include "problemes.h"
#include "premiers.h"

#include <execution>

typedef std::vector<size_t> vecteur;

ENREGISTRER_PROBLEME(10, "Summation of primes") {
    // The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
    // 
    // Find the sum of all the primes below two million.
    vecteur premiers;
    premiers::crible2<size_t>(2000000, std::back_inserter(premiers));
    size_t solution = std::reduce(std::execution::par, premiers.begin(), premiers.end());
    return std::to_string(solution);
}
