#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <map>
#include <set>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble; 

ENREGISTRER_PROBLEME(159, "Digital root sums of factorisations")
{
    // A composite number can be factored many different ways. For instance, not including 
    // multiplication by one, 24 can be factored in 7 distinct ways:
    //
    //       24 = 2x2x2x3
    //       24 = 2x3x4
    //       24 = 2x2x6
    //       24 = 4x6
    //       24 = 3x8
    //       24 = 2x12
    //       24 = 24
    //
    // Recall that the digital root of a number, in base 10, is found by adding together the 
    // digits of that number, and repeating that process until a number is arrived at that is
    // less than 10. Thus the digital root of 467 is 8.
    //
    // We shall call a Digital Root Sum (DRS) the sum of the digital roots of the individual 
    // factors of our number.
    // The chart below demonstrates all of the DRS values for 24.
    //
    //                  Factorisation   Digital Root Sum
    //                        2x2x2x3                  9
    //                          2x3x4                  9
    //                          2x2x6                 10
    //                            4x6                 10
    //                            3x8                 11
    //                           2x12                  5
    //                             24                  6
    //
    // The maximum Digital Root Sum of 24 is 11.
    // The function mdrs(n) gives the maximum Digital Root Sum of n. So mdrs(24)=11.
    // Find ∑mdrs(n) for 1 < n < 1,000,000.
    nombre limite = 1000000;
    
    vecteur maximumDRS(limite, 0);
    maximumDRS[0] = 0;
    maximumDRS[1] = 0;
    for (nombre n = 2; n < limite; ++n)
    {
        nombre k = n % 9;
        maximumDRS[n] = k ? k : 9;
        // maximumDRS[n] = arithmetiques::somme_chiffres(n);
    }
        
    for (nombre i = 2; 2 * i < limite; ++i)
    for (nombre j = 2; i * j < limite; ++j)
    {
        maximumDRS[i*j] = std::max(maximumDRS[i*j], maximumDRS[i] + maximumDRS[j]);
    }
    
    std::cout << "maximumDRS[24] = " << maximumDRS[24] << std::endl;
    
    nombre resultat = std::accumulate(maximumDRS.begin(), maximumDRS.end(), 0ULL);
    std::cout << "Solution: " << resultat << std::endl;
}
