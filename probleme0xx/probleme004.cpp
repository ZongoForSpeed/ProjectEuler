#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(4, "Largest palindrome product")
{
    // A palindromic number reads the same both ways. The largest palindrome made from the product 
    // of two 2-digit numbers is 9009 = 91 × 99.
    // 
    // Find the largest palindrome made from the product of two 3-digit numbers.
    auto palindrome = [](const nombre & n) -> bool
    {
        std::string s = std::to_string(n);
        return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
    };
    
    nombre solution = 0;
    for (nombre a = 100; a < 1000; ++a)
    {
        for (nombre b = 100; b < a; ++b)
        {
            nombre ab = a*b;
            if (palindrome(ab))
                solution = std::max(solution, ab);
        }
    }
    return std::to_string(solution);
}
