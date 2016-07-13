#include "problemes.h"
#include "polygonal.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(142, "Perfect Square Collection")
{
    // Find the smallest x + y + z with integers x > y > z > 0 such that x + y, x − y, x + z, x − z,
    // y + z, y − z are all perfect squares.
	nombre limite = 7000;
	
	nombre resultat = std::numeric_limits<nombre>::max();
    for(nombre a = 1; a < limite; ++a) 
    {
        nombre a2 = a*a;
        nombre parite = a%2;
        if (parite == 0)
            parite = 2;
            
        for(nombre c=parite; c < a; c += 2) 
        {
            nombre c2 = c*c;
            if (!polygonal::est_carre(a2 - c2))
                continue;
            
            for(nombre b = parite; b < c; b += 2) 
            {
                nombre b2 = b*b;
                if (2*c2 < a2 + b2)
                    continue;
                
                if (!polygonal::est_carre(c2 - b2) || !polygonal::est_carre(a2 + b2 - c2)) 
                    continue;
                
                nombre x = (a2 + b2)/2;
                nombre y = (a2 - b2)/2;
                nombre z = c2 - x;
                resultat = std::min(resultat, x+y+z);
            }
            
        }
    }
	// nombre resultat = std::accumulate(solutions.begin(), solutions.end(), 0ULL);
    return std::to_string(resultat);
}

