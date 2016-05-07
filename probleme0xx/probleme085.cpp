#include "problemes.h"
#include "polygonal.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cmath>

typedef long long nombre;

ENREGISTRER_PROBLEME(85, "Counting rectangles")
{
    // By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains 
    // eighteen rectangles:
    //
    // Although there exists no rectangular grid that contains exactly two million rectangles, 
    // find the area of the grid with the nearest solution.
    const nombre borne = 2000000;
    const nombre limite = 2000;
    
    nombre minimum = std::numeric_limits<nombre>::max();
    nombre resultat = 0;
    for (nombre i = 1; i <= limite; ++i)
    {
        for (nombre j = 1; j <= i; ++j)
        {
            const nombre triangle_ij = polygonal::triangulaire(j) * polygonal::triangulaire(i);
            if (std::llabs(borne - triangle_ij) < minimum)
            {
                minimum = std::llabs(borne - triangle_ij);
                resultat = i*j;
            }
            if (triangle_ij > borne)
                break;
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}