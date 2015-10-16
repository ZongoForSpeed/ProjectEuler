#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef unsigned long long nombre;
// typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

namespace
{
    long double aire(long double a, long double b, long double c)
    {
        // Aire = \dfrac{1}{4}\sqrt{(a+b+c)(-a+b+c)(a-b+c)(a+b-c)}=\sqrt{p(p-a)(p-b)(p-c)}.
        long double aire2 = (a+b+c)*(b+c-a)*(a+c-b)*(a+b-c) / 16.0;
        return std::sqrt(aire2);
    }
}

ENREGISTRER_PROBLEME(195)
{
    Timer timer("probleme 195");
    // Let's call an integer sided triangle with exactly one angle of 60 degrees a 60-degree triangle.
    // Let r be the radius of the inscribed circle of such a 60-degree triangle.
    //
    // There are 1234 60-degree triangles for which r ≤ 100. 
    // Let T(n) be the number of 60-degree triangles for which r ≤ n, so
    // T(100) = 1234,  T(1000) = 22767, and  T(10000) = 359912.
    //
    // Find T(1053779).
    nombre limite = 1053779;
    nombre borne = 2*std::sqrt(limite);

    // a = m² - mn + n² 
    // b = 2mn - n² 
    // c = m² - n²
    // 0 < 2*n < m
    nombre resultat = 0;
    std::cout << std::boolalpha;
    for (nombre n = 1; n < borne; ++n)
    {
        for (nombre m = 2*n + 1;; ++m)
        {
            if (arithmetiques::PGCD(m, n) == 1)
            {
                nombre a = m*m - m*n + n*n;
                nombre b = 2*m*n - n*n;
                nombre c = m*m - n*n;
                nombre pgcd = arithmetiques::PGCD(a, arithmetiques::PGCD(b, c));
                a /= pgcd;
                b /= pgcd;
                c /= pgcd;
                // r = 2.S / (a+b+c)
                long double r = 2*aire(a,b,c) / (a+b+c);
                if (r > 3*limite)
                    break;
                    
                if (r < limite)
                {
                    resultat += std::floor(limite / r);
                }
            }
        }    
    }

    
    std::cout << "Solution: " << resultat << std::endl;
}
