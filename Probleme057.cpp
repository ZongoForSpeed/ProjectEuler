#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>

typedef boost::multiprecision::cpp_int nombre;
typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(57)
{
    Timer t("probleme 57");
    // It is possible to show that the square root of two can be expressed as an infinite continued fraction.
    //
    //                              √ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
    //
    // By expanding this for the first four iterations, we get:
    //
    //      1 + 1/2 = 3/2 = 1.5
    //      1 + 1/(2 + 1/2) = 7/5 = 1.4
    //      1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
    //      1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
    //
    // The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the 
    // first example where the number of digits in the numerator exceeds the number of digits in the denominator.
    // 
    // In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator?
    fraction f(3, 2);
    nombre compteur = 0;
    for (nombre n = 1; n < 1000; ++n)
    {
        f = 1 + 1 / (1 + f);
        if (chiffres::nombre_chiffres(f.numerator()) > chiffres::nombre_chiffres(f.denominator()))
        {
            ++compteur;
        }
    }

    std::cout << "Solution: " << compteur << std::endl;
}