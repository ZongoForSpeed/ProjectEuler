#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(100, "Arranged probability")
{
    // If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs,
    // and two discs were taken at random, it can be seen that the probability of taking two blue 
    // discs, P(BB) = (15/21)×(14/20) = 1/2.
    //
    // The next such arrangement, for which there is exactly 50% chance of taking two blue discs at 
    // random, is a box containing eighty-five blue discs and thirty-five red discs.
    // 
    // By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total, 
    // determine the number of blue discs that the box would contain.
    nombre limite = 1000000000000;
    nombre b = 85;
    nombre n = 120;
    while (n < limite)
    {
        std::tie(b,n) = std::make_pair(3*b + 2*n - 2, 4*b + 3*n - 3);
    }
    
    nombre resultat = b;
    std::cout << "Solution: " << resultat << std::endl;
}
