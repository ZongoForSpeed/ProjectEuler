#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(115, "Counting block combinations II")
{
    Timer t("probleme 115");
    // NOTE: This is a more difficult version of Problem 114.
    //
    // A row measuring n units in length has red blocks with a minimum length of m units placed on it,
    // such that any two red blocks (which are allowed to be different lengths) are separated by at 
    // least one black square.
    // 
    // Let the fill-count function, F(m, n), represent the number of ways that a row can be filled.
    // 
    // For example, F(3, 29) = 673135 and F(3, 30) = 1089155.
    // 
    // That is, for m = 3, it can be seen that n = 30 is the smallest value for which the fill-count 
    // function first exceeds one million.
    // 
    // In the same way, for m = 10, it can be verified that F(10, 56) = 880711 and F(10, 57) = 1148904, 
    // so n = 57 is the least value for which the fill-count function first exceeds one million.
    //
    // For m = 50, find the least value of n for which the fill-count function first exceeds one million.
    nombre limite = 1000000;
    nombre m = 50;
    vecteur valeur(m, 1);
    valeur.push_back(2);
    
    nombre resultat = 0;
    for(nombre n = m + 1;; ++n)
    {
        nombre v = valeur.back() + 2;
        for (nombre k = 1; k < n - m; ++k)
            v += valeur[k];
        valeur.push_back(v);
        if (v > limite)
        {
            resultat = n;
            break;
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
