#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <map>
#include <set>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(160)
{
    Timer timer("probleme 160");
	// For any N, let f(N) be the last five digits before the trailing zeroes in N!.
    // For example,
    // 
    //      9! = 362880 so f(9)=36288
    //      10! = 3628800 so f(10)=36288
    //      20! = 2432902008176640000 so f(20)=17664
    //
    // Find f(1,000,000,000,000)
    nombre limite = 1000000000000ULL;
    nombre masque = 100000;
    
    // f(1,000,000,000,000) = f(2560000)
    while (limite % 5 == 0)
        limite /= 5;
    limite *= puissance::puissance(5, 4);

    nombre resultat = 1;
    nombre facteur2 = 0;
    nombre facteur5 = 0;
    for (nombre n = 1; n < limite + 1; ++n)
    {
        nombre m = n;
        while (m%5 == 0)
        {
            ++facteur5;
            m /= 5;
        }
    
        while (m%2 == 0)
        {
            ++facteur2;
            m /= 2;
        }
        resultat = (resultat * m)%masque;
    }
    resultat = (resultat * puissance::puissance_modulaire<nombre>(2, facteur2 - facteur5, masque))%masque;
    std::cout << "Solution: " << resultat << std::endl;
}
