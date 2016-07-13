#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(154, "Exploring Pascal's pyramid")
{
	// A triangular pyramid is constructed using spherical balls so that each ball rests on exactly 
	// three balls of the next lower level.
    //
    // Then, we calculate the number of paths leading from the apex to each position:
    // 
    // A path starts at the apex and progresses downwards to any of the three spheres directly below
    // the current position.
    // 
    // Consequently, the number of paths to reach a certain position is the sum of the numbers immediately
    // above it (depending on the position, there are up to three numbers above it).
    // 
    // The result is Pascal's pyramid and the numbers at each level n are the coefficients of the 
    // trinomial expansion (x + y + z)^n.
    // 
    // How many coefficients in the expansion of (x + y + z)^200000 are multiples of 10^12?
    nombre n = 200000;
    
    vecteur deux(n + 1, 0);
    vecteur cinq(n + 1, 0);
    
    for (nombre i = 1; i <= n; ++i)
    {
        deux[i] = deux[i - 1] + arithmetiques::nombre_facteur(i, 2UL);
        cinq[i] = cinq[i - 1] + arithmetiques::nombre_facteur(i, 5UL);
    }
    
    // C(n,i,j) = n! / i!j!(n-i-j)!
    nombre resultat = 0;
    for (nombre i = 0; i <= n; ++i)
    for (nombre j = 0; j <= n - i; ++j)
    {
        if (cinq[n] - cinq[i] - cinq[j] - cinq[n-i-j] >= 12
            && deux[n] - deux[i] - deux[j] - deux[n-i-j] >= 12)
            ++resultat;
    }
    
    return std::to_string(resultat);
}
