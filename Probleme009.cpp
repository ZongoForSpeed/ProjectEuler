#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <boost/tuple/tuple.hpp>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(9)
{
    // A Pythagorean triplet is a set of three natural numbers, a < b < c, for which, a² + b² = c²
    // For example, 3² + 4² = 9 + 16 = 25 = 5².
    //
    // There exists exactly one Pythagorean triplet for which a + b + c = 1000.
    // Find the product abc.
    Timer t("probleme 9");
    auto pythagorean = [](const nombre & limite) -> boost::tuple<nombre, nombre, nombre>
    {
        for (nombre a = 1; a < limite / 3; ++a)
        {
            for (nombre b = a + 1; b < limite / 2; ++b)
            {
                nombre c = limite - a - b;
                if (a*a + b*b == c*c)
                    return boost::tuple<nombre, nombre, nombre>(a,b,c);
            }
        }
        return boost::tuple<nombre, nombre, nombre>(0, 0, 0);
    };
    nombre a,b,c;
    boost::tie(a, b, c) = pythagorean(1000);
    std::cout << "Solution: " << a*b*c << " (a, b, c) = (" << a << ", " << b << ", " << c << ")" << std::endl;
}
