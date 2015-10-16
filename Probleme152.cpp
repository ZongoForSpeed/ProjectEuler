#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

#include <boost/rational.hpp>
#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<size_t> vecteur;
typedef boost::rational<nombre> fraction;

namespace
{
    size_t generer(const vecteur & premiers, size_t p, fraction f = fraction(0), size_t a = 0)
    {
        fraction objectif(1, 2);
        size_t resultat = 0;
        for (size_t m = a + 1; m*p < 80 + 1; ++m)
        {
            size_t q = m;
            // remove factors f<=p
            for (size_t pp: premiers)
            {
                if (pp > p)
                    break;
                while (q%pp == 0) 
                    q = q / pp;    		    
            }
            
            // m has factors f<=p only
            if (q==1)
            {
                fraction f1 = f + fraction(1, m*m*p*p);
                if (f1 == objectif)
                    ++resultat;
                else 
                {
                    if (f1.denominator()%p != 0)
                        for (size_t pp: premiers)
                            if (pp < p) resultat += generer(premiers, pp, f1);
                    resultat += generer(premiers, p, f1, m);
                }
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(152)
{
    Timer timer("probleme 152");
	// There are several ways to write the number 1/2 as a sum of inverse squares using distinct integers.
    //
    // For instance, the numbers {2,3,4,5,7,12,15,20,28,35} can be used:
    //
    //      1/2 = 1/2² + 1/3² + 1/4² + 1/5² + 1/7² + 1/12² + 1/15² + 1/20² + 1/28² + 1/35²
    //
    // In fact, only using integers between 2 and 45 inclusive, there are exactly three ways to do it, 
    // the remaining two being: {2,3,4,6,7,9,10,20,28,35,36,45} and {2,3,4,6,7,9,12,15,28,30,35,36,45}.
    //
    // How many ways are there to write the number 1/2 as a sum of inverse squares using distinct integers
    // between 2 and 80 inclusive?
    vecteur premiers;
    premiers::crible<size_t>(40, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for (size_t p: premiers)
        resultat += generer(premiers, p);

    std::cout << "Solution: " << resultat << std::endl;
}
