#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(7)
{
    // By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
    // 
    // What is the 10 001st prime number?
    Timer t("probleme 7");
    vecteur premiers;
    premiers::crible<nombre>(200000, std::back_inserter(premiers));
    nombre solution = premiers.at(10000);
    std::cout << "Solution: " << solution << std::endl;
}
