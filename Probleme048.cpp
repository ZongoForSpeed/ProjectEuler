#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;

void probleme048()
{
    Timer t("probleme 48");
    // The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
    //
    // Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    nombre resultat = 0;
    for (nombre n = 1; n <= 1000; ++n)
    {
        resultat += puissance::puissance_modulaire(n, n, 10000000000LL);
        resultat = resultat%10000000000LL; 
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}