#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef boost::rational<nombre> fraction;

void probleme071()
{
    Timer t("probleme 71");
    // Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is 
    // called a reduced proper fraction.
    //
    // If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
    // 
    // 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
    // 
    // It can be seen that 2/5 is the fraction immediately to the left of 3/7.
    // 
    // By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, 
    // find the numerator of the fraction immediately to the left of 3/7.
    fraction objectif(3, 7);
    fraction ratio_min (1);
    fraction resultat(1);
    for (nombre d = 2; d <= 1000000; ++d)
    {
        nombre n = objectif.numerator() * d / objectif.denominator();
        fraction ratio = objectif - fraction(n, d);
        if (ratio> 0 && ratio < ratio_min)
        {
            ratio_min = ratio;
            resultat = fraction(n, d);
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}