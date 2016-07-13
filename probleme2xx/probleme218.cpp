#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(218, "Perfect right-angled triangles")
{
    // Consider the right angled triangle with sides a=7, b=24 and c=25. The area of this triangle 
    // is 84, which is divisible by the perfect numbers 6 and 28.
    // Moreover it is a primitive right angled triangle as gcd(a,b)=1 and gcd(b,c)=1.
    // Also c is a perfect square.
    //
    // We will call a right angled triangle perfect if
    // -it is a primitive right angled triangle
    // -its hypotenuse is a perfect square
    //
    // We will call a right angled triangle super-perfect if
    // -it is a perfect right angled triangle and
    // -its area is a multiple of the perfect numbers 6 and 28.
    //
    // How many perfect right-angled triangles with c ≤ 10^16 exist that are not super-perfect?
    nombre limite = puissance::puissance<nombre>(10, 16);
    nombre limite_m = puissance::puissance<nombre>(10, 4);
    nombre resultat = 0;

    for (nombre m = 2; m < limite_m; ++m)
    for (nombre n = m%2 + 1; n < m; n += 2)
    {
        if (arithmetiques::PGCD(m, n) == 1)
        {
            nombre x = m*m - n*n;
            nombre y = 2*m*n;
            
            nombre z = m*m + n*n;
            
            if (x < y) std::swap(x, y);
            
            nombre a = x*x - y*y;
            nombre b = 2*x*y;
            nombre c = z*z;
            if (c > limite)
                break;
                
            // std::cout << std::make_tuple(a, b, c) << std::endl;
            nombre A = a*b / 2;
            if (A%6 != 0 || A%28 != 0)
                ++resultat;
        }
    }
    
    return std::to_string(resultat);
}
