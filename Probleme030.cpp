#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

typedef unsigned long long nombre;   
    
ENREGISTRER_PROBLEME(30, "Digit fifth powers")
{
    Timer t("probleme 30");
    // Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
    // 
    // 1634 = 1^4 + 6^4 + 3^4 + 4^4
    // 8208 = 8^4 + 2^4 + 0^4 + 8^4
    // 9474 = 9^4 + 4^4 + 7^4 + 4^4
    // As 1 = 1^4 is not a sum it is not included.
    //
    // The sum of these numbers is 1634 + 8208 + 9474 = 19316.
    // 
    // Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
    nombre resultat = 0;
    for (nombre n = 2; n < 200000; ++n)
    {
        nombre s = 0;
        chiffres::boucle_chiffre(n, [&s](nombre d) { s += puissance::puissance(d, 5); });
        if (s == n) resultat += n;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
