#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

void probleme016()
{
    Timer t("probleme 16");
    // 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
    //
    // What is the sum of the digits of the number 2^1000?
    nombre n = puissance::puissance<nombre>(2, 1000);
    nombre resultat = 0;
    arithmetiques::boucle_chiffre(n, [&resultat](nombre d) { resultat += d; });
    std::cout << "Solution: " << resultat << std::endl;
}