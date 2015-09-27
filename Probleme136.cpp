#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme136()
{
    Timer t("probleme 136");
    // The positive integers, x, y, and z, are consecutive terms of an arithmetic progression. 
    // Given that n is a positive integer, the equation, x² − y² − z² = n, has exactly one solution
    // when n = 20:
    //
    //                                          13² − 10² − 7² = 20
    //
    // In fact there are twenty-five values of n below one hundred for which the equation has a unique
    // solution.
    //
    // How many values of n less than fifty million have exactly one solution?
    nombre limite = 50000000;
    vecteur compteur(limite, 0);
    
    for (nombre x = 1; x < limite; ++x)
    {
        for (nombre m = (x + 2) / 3; m < limite; ++m)
        {
            nombre n = (m + x)*(3*m - x);
            if (n < limite)
                compteur[n]++;
            else
                break;
        }
    }
    
    nombre resultat = std::count (compteur.begin(), compteur.end(), 1);
    std::cout << "Solution: " << resultat << std::endl;
}
