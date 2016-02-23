#include "problemes.h"
#include "chiffres.h"
#include "timer.h"

#include <iostream>
#include <algorithm>
#include <sstream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(38, "Pandigital multiples")
{
    Timer t("probleme 38");
    // Take the number 192 and multiply it by each of 1, 2, and 3:
    //
    //    192 × 1 = 192
    //    192 × 2 = 384
    //    192 × 3 = 576
    //
    // By concatenating each product we get the 1 to 9 pandigital, 192384576.
    // We will call 192384576 the concatenated product of 192 and (1,2,3)
    //
    // The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5,
    // giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
    //
    // What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated
    // product of an integer with (1,2, ... , n) where n > 1?
    auto algorithme = [&](const nombre & n) -> nombre
    {
        if (!chiffres::pandigital(n))
            return 0;
        std::stringstream ss;
        nombre resultat = n;
        ss << n;
        nombre m = 2;
        nombre f;
        while (m<=9)
        {
            ss << m*n;
            ss >> f;
            if (!chiffres::pandigital(f))
                return resultat;
            resultat = f;
            ++m;
        }
        return resultat;
    };

    nombre resultat = 0;
    for (nombre i = 1; i < 100000; ++i)
    {
        if (i%5 != 0)
            resultat = std::max(resultat, algorithme(i));
    }
    std::cout << "Solution: " << resultat << std::endl;
}
