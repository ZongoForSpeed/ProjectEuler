#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(179, "Consecutive positive divisors")
{
    Timer timer("probleme 179");
    // Find the number of integers 1 < n < 107, for which n and n + 1 have the same number of positive 
    // divisors. For example, 14 has the positive divisors 1, 2, 7, 14 while 15 has 1, 3, 5, 15.
    nombre limite = 10000000;
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));
    
    nombre resultat = 0;
    nombre sigma = 1;
    for (nombre n = 2; n < limite; ++n)
    {
        nombre s = arithmetiques::nombre_diviseurs(n, premiers);
        if (sigma == s)
            ++resultat;
        else 
            sigma = s;
    }
    std::cout << "Solution: " << resultat << std::endl;
}
