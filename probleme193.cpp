#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(193, "Squarefree Numbers")
{
    Timer timer("probleme 193");
    // A positive integer n is called squarefree, if no square of a prime divides n, thus 1, 2, 3, 5, 
    // 6, 7, 10, 11 are squarefree, but not 4, 8, 9, 12.
    //
    // How many squarefree numbers are there below 2^50?
    nombre limite = puissance::puissance<nombre>(2, 25);
    vecteur premiers;
    premiers::crible235<nombre>((size_t)limite, std::back_inserter(premiers));
    
    // N=2^50-1;
    // sum(k=1,sqrt(N),floor(N/k^2)*moebius(k))
    
    nombre resultat = 0;
    for (nombre k = 1; k < limite; ++k)
    {
        resultat += arithmetiques::moebius(k, premiers) * limite*limite / (k*k);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
