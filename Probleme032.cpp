#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long nombre;

void probleme032()
{
    Timer t("probleme 32");
    // We shall say that an n-digit number is pandigital if it makes use of all the digits 1 
    // to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
    //
    // The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, 
    // multiplier, and product is 1 through 9 pandigital.
    // 
    // Find the sum of all products whose multiplicand/multiplier/product identity can be written 
    // as a 1 through 9 pandigital.
    //
    // HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
    std::vector<unsigned short> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::set<nombre> resultat;
    do 
    {
        for (size_t i = 1; i < 8; ++i)
        {
            nombre a = chiffres::conversion_nombre<nombre>(v.begin(), v.begin() + i);
            for (size_t j = i + 1; j < 9; ++j)
            {
                nombre b = chiffres::conversion_nombre<nombre>(v.begin() + i, v.begin() + j);
                nombre c = chiffres::conversion_nombre<nombre>(v.begin() + j, v.end());
                if (a * b == c)
                {
                    std::cout << a << " * " << b << " = " << c << std::endl;  
                    resultat.insert(c);
                }
            }
        }
    } 
    while (std::next_permutation(v.begin(), v.end()));
    nombre solution = std::accumulate(resultat.begin(), resultat.end(), 0);
    std::cout << "Solution: " << solution << std::endl;
}
