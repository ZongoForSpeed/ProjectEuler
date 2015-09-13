#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <functional>

#include <boost/rational.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

void probleme065()
{
    Timer t("probleme 65");
    // The square root of 2 can be written as an infinite continued fraction.
    // 
    // The infinite continued fraction can be written, √2 = [1;(2)], (2) indicates that 2 repeats ad infinitum. In a similar way, √23 = [4;(1,3,1,8)].
    //
    // It turns out that the sequence of partial values of continued fractions for square roots provide the best rational approximations. Let us consider the convergents for √2.
    // 
    // Hence the sequence of the first ten convergents for √2 are:
    // 
    // 1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985, 3363/2378, ...
    // What is most surprising is that the important mathematical constant,
    // e = [2; 1,2,1, 1,4,1, 1,6,1 , ... , 1,2k,1, ...].
    // 
    // The first ten terms in the sequence of convergents for e are:
    // 
    // 2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
    // The sum of digits in the numerator of the 10th convergent is 1+4+5+7=17.
    // 
    // Find the sum of digits in the numerator of the 100th convergent of the continued fraction for e.
    vecteur fraction_continue;
    fraction_continue.push_back(2);
    for (nombre n = 2; n < 101; n += 2)
    {
        fraction_continue.push_back(1);
        fraction_continue.push_back(n);
        fraction_continue.push_back(1);
    }
    fraction_continue.resize(99);
    fraction f(1);
    for (auto p: boost::adaptors::reverse(fraction_continue)) f = p + 1 / f;
    
    auto chiffres = arithmetiques::extraire_chiffres(f.numerator());
    nombre resultat = std::accumulate(chiffres.begin(), chiffres.end(), nombre(0));
    std::cout << "Solution: " << resultat << std::endl;
}