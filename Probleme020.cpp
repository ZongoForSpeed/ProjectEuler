#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

void probleme020()
{
    Timer t("probleme 20");
    // n! means n × (n − 1) × ... × 3 × 2 × 1
    // 
    // For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
    // and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
    // 
    // Find the sum of the digits in the number 100!
    nombre factorielle = combinatoire::factorielle<nombre>(100);
    nombre resultat = 0;
    arithmetiques::boucle_chiffre(factorielle, [&resultat](nombre d) { resultat += d; });
    std::cout << "Solution: " << resultat << std::endl;
}
