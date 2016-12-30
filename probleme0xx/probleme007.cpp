#include "problemes.h"
#include "premiers.h"

#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(7, "10001st prime")
{
    // By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
    // 
    // What is the 10 001st prime number?
    vecteur premiers;
    premiers::crible235<nombre>(200000, std::back_inserter(premiers));
    nombre solution = premiers.at(10000);
    return std::to_string(solution);
}
