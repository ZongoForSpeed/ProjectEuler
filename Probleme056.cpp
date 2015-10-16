#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(56)
{
    Timer t("probleme 56");
    // A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost 
    // unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the 
    // digits in each number is only 1.
    //
    // Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
    nombre maximum = 0;
    for (nombre a = 1; a < 100; ++a)
    for (nombre b = 1; b < 100; ++b)
    {
        nombre somme = 0;
        chiffres::boucle_chiffre(puissance::puissance(a,b), [&somme] (const nombre & d) { somme += d; });
        maximum = std::max(maximum, somme);
    }
    std::cout << "Solution: " << maximum << std::endl;
}