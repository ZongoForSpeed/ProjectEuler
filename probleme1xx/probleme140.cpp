#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(140, "Modified Fibonacci golden nuggets")
{
    Timer t("probleme 140");
    // Consider the infinite polynomial series AG(x) = xG1 + x2G2 + x3G3 + ..., where Gk is the kth 
    // term of the second order recurrence relation Gk = Gk−1 + Gk−2, G1 = 1 and G2 = 4; that is, 
    // 1, 4, 5, 9, 14, 23, ... .
    //
    // For this problem we shall be concerned with values of x for which AG(x) is a positive integer.
    // 
    // The corresponding values of x for the first five natural numbers are shown below.
    //
    //                                          x           AG(x)
    //                                          (√5−1)/4	1
    //                                          2/5         2
    //                                          (√22−2)/6	3
    //                                          (√137−5)/14	4
    //                                          1/2	        5
    //
    // We shall call AG(x) a golden nugget if x is rational, because they become increasingly rarer; 
    // for example, the 20th golden nugget is 211345365.
    //
    // Find the sum of the first thirty golden nuggets.
    vecteur fibonacci { 0, 1, 1 };
    for (size_t n = 3; n < 80; ++n)
        fibonacci.push_back(fibonacci.back() + fibonacci.at(n-2));

    auto nugget = [] (fraction x) -> nombre 
    {
        x = (1 + 3*x)*x / (1 - x - x*x); 
        return x.numerator() / x.denominator();
    };
    
    size_t objectif = 30;
    nombre resultat = 0;
    for (size_t n = 3, i = 4; n < objectif + 2; n += 2, i += 4)
    {
        nombre v = nugget(fraction(fibonacci[n-1], fibonacci[n]));
        resultat += 2*v - fibonacci[i];
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}

