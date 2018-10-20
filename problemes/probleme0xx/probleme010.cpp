#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(10, "Summation of primes") {
    // The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
    // 
    // Find the sum of all the primes below two million.
    vecteur premiers;
    premiers::crible2<nombre>(2000000, std::back_inserter(premiers));
    nombre solution = std::accumulate(premiers.begin(), premiers.end(), nombre(0));
    return solution.convert_to<std::string>();
}
