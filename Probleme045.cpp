#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;

void probleme045()
{
    Timer t("probleme 45");
    // Triangle, pentagonal, and hexagonal numbers are generated by the following formulae:
    // Triangle        Tn=n(n+1)/2         1, 3, 6, 10, 15, ...
    // Pentagonal      Pn=n(3n−1)/2        1, 5, 12, 22, 35, ...
    // Hexagonal       Hn=n(2n−1)      1, 6, 15, 28, 45, ...
    //
    // It can be verified that T285 = P165 = H143 = 40755.
    //
    // Find the next triangle number that is also pentagonal and hexagonal.
    nombre resultat = 0;
    nombre n = 286;
    while (true)
    {
        nombre t = polygonal::triangulaire(n);
        if (polygonal::est_hexagonal(t) && polygonal::est_pentagonal(t))
        {
            resultat = t;
            break;
        }
        ++n;
    }
    std::cout << "Solution: " << resultat << std::endl;
}