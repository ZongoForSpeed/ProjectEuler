#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(202, "\"Laserbeam\"")
{
    Timer timer("probleme 202");
    // Three mirrors are arranged in the shape of an equilateral triangle, with their reflective surfaces 
    // pointing inwards. There is an infinitesimal gap at each vertex of the triangle through which 
    // a laser beam may pass.
    //
    // Label the vertices A, B and C. There are 2 ways in which a laser beam may enter vertex C, bounce 
    // off 11 surfaces, then exit through the same vertex: one way is shown below; the other is the 
    // reverse of that.
    //
    // There are 80840 ways in which a laser beam may enter vertex C, bounce off 1000001 surfaces, 
    // then exit through the same vertex.
    //
    // In how many ways can a laser beam enter at vertex C, bounce off 12017639147 surfaces, then exit 
    // through the same vertex?
    nombre resultat = 0;
    nombre limite = 12017639147;
    for (nombre m = 1; 2*m < limite + 3; ++m)
    {
        nombre n = (limite + 3) / 2 - m;
        if (m > n) break;
        nombre d = n - m;
        if (d%3 == 0 && arithmetiques::PGCD(m, n) == 1)
        {
            ++resultat;
            // std::cout << "n = " << n << ", m = " << m << std::endl;
        }
    }
    
    resultat *= 2;
    
    std::cout << "Solution: " << resultat << std::endl;
}
