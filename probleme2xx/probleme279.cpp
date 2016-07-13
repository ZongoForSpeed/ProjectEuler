#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(279, "Triangles with integral sides and an integral angle")
{
    // How many triangles are there with integral sides, at least one integral 
    // angle (measured in degrees), and a perimeter that does not exceed 10**8?
    nombre limite = 100000000;
    
    nombre resultat = limite / 3;
    for (nombre m = 2; 2*m*m < limite; ++m)
    for (nombre n = 1; n < m; ++n)
    {
        if (arithmetiques::PGCD(m, n) == 1)
        {
            if ((m-n)%3 != 0)
            {
                resultat += limite / (2*m*m + 2*n*n + 5*m*n);
                resultat += limite / (3*m*m + 3*m*n);
                resultat += limite / (2*m*m + n*n + 3*m*n);
            }
            
            if ((m-n)%2 != 0)
            {
                resultat += limite / (2*m*m+2*m*n);
            }
        }
    }
    return std::to_string(resultat);
}
