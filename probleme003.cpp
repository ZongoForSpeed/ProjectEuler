#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

#include <iostream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(3, "Largest prime factor")
{
    // The prime factors of 13195 are 5, 7, 13 and 29.
    // 
    // What is the largest prime factor of the number 600851475143 ?
    Timer t ("probleme 3");
    nombre n = 600851475143LL;
    nombre d = 2;
    while (n != 1)
    {
        if (n%d == 0)
            n /= d;
        else
            ++d;
    }
    std::cout << "Solution: " << d << std::endl;
}