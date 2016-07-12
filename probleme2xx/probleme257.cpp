#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "chiffres.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// typedef boost::multiprecision::mpz_limite     nombre;

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(257, "Angular Bisectors")
{
    // Given is an integer sided triangle ABC with sides a ≤ b ≤ c. (AB = c, 
    // BC = a and AC = b).
    // The angular bisectors of the triangle intersect the sides at points E, F 
    // and G (see picture below).
    // 
    // p257_bisector.gif
    // The segments EF, EG and FG partition the triangle ABC into four smaller 
    // triangles: AEG, BFE, CGF and EFG.
    // It can be proven that for each of these four triangles the ratio 
    // area(ABC)/area(subtriangle) is rational.
    // However, there exist triangles for which some or all of these ratios are 
    // integral.
    //
    // How many triangles ABC with perimeter≤100,000,000 exist so that the ratio
    // area(ABC)/area(AEG) is integral?
    nombre limite = 100000000;
    const long double racine2 = std::sqrt(2.0);
    const long double racine3 = std::sqrt(3.0);

    nombre compteur = limite / 3; // Cas a = b = c
    
    for (nombre q = 1; q*q < limite; ++q)
    {
        for (nombre p = q + 1; p < racine2 * q; ++p)
        {
            // Cas (a+b)*(a+c) = 2*b*c
            if (arithmetiques::PGCD(p, q) == 1)
            {
                nombre d = (p%2 == 0) ? 2 : 1;
                nombre r = (p + q) * (p + 2 * q) / d;
                compteur += limite / r;
            }
        }
        
        for (nombre p = q + 1; p < racine3 * q; ++p)
        {
            // Cas (a+b)*(a+c) = 3*b*c
            if (arithmetiques::PGCD(p, q) == 1)
            {
                nombre d = ((p%3 == 0) ? 3 : 1) * (((p + q)%2 == 0) ? 2 : 1);
                nombre r = (p + q) * (p + 3 * q) / d;
                compteur += limite / r;
            }
        }
    }

    std::cout << "Solution: " << compteur << std::endl;
}
