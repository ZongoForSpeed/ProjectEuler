#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(48, "Self powers")
{
    // The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
    //
    // Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    nombre resultat = 0;
    for (size_t n = 1; n <= 1000; ++n)
    {
        resultat += puissance::puissance_modulaire<nombre>(n, n, 10000000000LL);
        resultat = resultat%10000000000LL; 
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
