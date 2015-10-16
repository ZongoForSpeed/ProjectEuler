#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(1, "Multiples of 3 and 5")
{
    // If we list all the natural numbers below 10 that are multiples of 3 or 5, 
    // we get 3, 5, 6 and 9. The sum of these multiples is 23.
    // 
    // Find the sum of all the multiples of 3 or 5 below 1000.
    Timer t ("probleme 1");
    nombre solution = 0;
    for (size_t n = 1; n < 1000; ++n)
    {
        if (n%3 == 0 || n%5 == 0)
            solution += n;
    }
    std::cout << "Solution: " << solution << std::endl;
}
