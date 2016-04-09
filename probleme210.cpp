#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"
#include "polygonal.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::pair<nombre, nombre> point;

namespace
{
    nombre points_cercle(nombre r)
    {
        nombre rayon2 = r*r/32;
        nombre rayon = racine_carre(rayon2);
        nombre resultat = 0;
        for (nombre x = 1; x <= rayon; ++x)
        {
            nombre y = racine_carre(rayon2 - x*x);
            resultat += y + 1;
        }
        
        return 4*resultat + 1;
    }
}

ENREGISTRER_PROBLEME(210, "Obtuse Angled Triangles")
{
    Timer timer("probleme 210");
    // Consider the set S(r) of points (x,y) with integer coordinates satisfying |x| + |y| ≤ r. 
    // Let O be the point (0,0) and C the point (r/4,r/4). 
    // Let N(r) be the number of points B in S(r), so that the triangle OBC has an obtuse angle, i.e. 
    // the largest angle α satisfies 90°<α<180°.
    // So, for example, N(4)=24 and N(8)=100.
    // What is N(1,000,000,000)?
    nombre r = 1000000000LL;
    // nombre r = 8;
    nombre resultat = 0;
    
    // domaine entier
    resultat += 2*r*(r + 1) + 1;
    // sans la bande 0 <= x+y <=r/2
    resultat -= (2*r + 1)*r/4 + r + 1;
    // sans les points y = x
    resultat -= r - 1;
    // points dans le cercle 
    resultat += points_cercle(r);
    
    // std::cout << "          1598174770174689458" << std::endl;
    std::cout << "Solution: " << resultat << std::endl;
}
