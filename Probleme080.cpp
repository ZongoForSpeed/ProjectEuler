#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

#include <gmpxx.h>

typedef mpz_class nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(80)
{
    Timer t("probleme 80");
    // It is well known that if the square root of a natural number is not an integer, then it is 
    // irrational. The decimal expansion of such square roots is infinite without any repeating 
    // pattern at all.
    //
    // The square root of two is 1.41421356237309504880..., and the digital sum of the first one 
    // hundred decimal digits is 475.
    //
    // For the first one hundred natural numbers, find the total of the digital sums of the first 
    // one hundred decimal digits for all the irrational square roots.
    nombre gogol = puissance::puissance(nombre(10), 100);
    nombre gogol_carre = gogol * gogol;
    
    std::ostringstream oss;
    for (size_t n = 1; n < 100; ++n)
    {
        if (!polygonal::est_carre(n))
        {
            std::ostringstream oss2;
            oss2 << sqrt(n * gogol_carre);
            oss << oss2.str().substr(0,100);
        }
    }
    
    nombre resultat = 0;
    for (auto c: oss.str())
    {
        resultat += (c - '0');
    }
    std::cout << "Solution: " << resultat << std::endl;
}