#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// #include <boost/multiprecision/cpp_int.hpp>
//
// typedef boost::multiprecision::mpz_int nombre;
typedef unsigned long long nombre;

namespace
{
    long double cercle(long double x)
    {
        return 0.5 - std::sqrt(0.0625 - (x - 0.25) * (x - 0.25));
    }
    
    long double s(long double x)
    {
        long double n = std::floor(x);
        return std::min(x - n, n + 1 - x);
    }
    
    long double blanc(long double x, size_t precision = 50)
    {
        long double resultat = 0.0;
        nombre exposant = 1;
        for (size_t n = 0; n < precision; ++n)
        {
            resultat += s(exposant*x)/exposant;
            exposant *= 2;
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(226, "A Scoop of Blancmange")
{
    Timer timer("probleme 226");
    // The blancmange curve is the set of points (x,y) such that 0 ≤ x ≤ 1 and y = Sum(s(2^n.x)/2^n, n = 0..Inf),
    // where s(x) = the distance from x to the nearest integer.
    // 
    // The area under the blancmange curve is equal to ½, shown in pink in the diagram below.
    // 
    // https://projecteuler.net/project/images/p226_scoop2.gif
    // 
    // Let C be the circle with centre (¼,½) and radius ¼, shown in black in the diagram.
    // 
    // What area under the blancmange curve is enclosed by C?
    // Give your answer rounded to eight decimal places in the form 0.abcdefgh
    long double resultat = 0.0;
    const long double dx = 0.000001;
    
    for (long double x = 0.0; x <= 0.5; x += dx)
    {
        long double y = blanc(x) - cercle(x);
        if (y > 0)
            resultat += y * dx;
    }
    
    std::cout << std::setprecision(8);
    std::cout << "Solution: " << resultat << std::endl;
}
