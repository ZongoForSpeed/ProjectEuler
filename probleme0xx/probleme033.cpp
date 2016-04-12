#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

#include <iostream>

#include <boost/rational.hpp>

typedef unsigned short nombre;
typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(33, "Digit cancelling fractions")
{
    Timer t("probleme 33");
    // The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting 
    // to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by 
    // cancelling the 9s.
    //
    // We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
    // 
    // There are exactly four non-trivial examples of this type of fraction, less than one in value, 
    // and containing two digits in the numerator and denominator.
    //
    // If the product of these four fractions is given in its lowest common terms, find the value of 
    // the denominator.
    fraction resultat(1);
    for (nombre a = 1; a < 10; ++a)
    for (nombre b = 1; b < 10; ++b)
    for (nombre c = 1; c < 10; ++c)
    {
        // nombre ac = a*10 + c;
        nombre bc = b*10 + c;
        nombre ab = a*10 + b;
        if (a != b && ab * c == bc * a)
        {
            std::cout << "(" << ab << " / " << bc << ") ";
            resultat *= fraction(ab, bc);
        }
    }
    std::cout << "solution: " << resultat.denominator() << std::endl;
}
