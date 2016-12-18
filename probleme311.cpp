#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "combinatoire.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> triplet;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre arrondi(nombre n, nombre d)
    {
        return n - n%d;
    }
}
ENREGISTRER_PROBLEME(311, "Biclinic Integral Quadrilaterals")
{
    // BCD is a convex, integer sided quadrilateral with 1 ≤ AB < BC < CD < AD.
    // BD has integer length. O is the midpoint of BD. AO has integer length.
    // We'll call ABCD a biclinic integral quadrilateral if AO = CO ≤ BO = DO.
    //
    // For example, the following quadrilateral is a biclinic integral quadrilateral:
    // AB = 19, BC = 29, CD = 37, AD = 43, BD = 48 and AO = CO = 23.
    //
    // p311_biclinic.gif
    // Let B(N) be the number of distinct biclinic integral quadrilaterals ABCD 
    // that satisfy AB² + BC² + CD² + AD² ≤ N.
    // We can verify that B(10 000) = 49 and B(1 000 000) = 38239.
    //
    // Find B(10 000 000 000).
    nombre limite = 10000000000;
    limite /= 2;
    
    nombre resultat = 0;
    nombre S = 100000000;
    
    for (nombre i = 0; i < limite / S + 1; ++i)
    {
        nombre L = i*S;
        nombre U = (i + 1)*S;
        vecteur compteurs(S/2, 0);
        
        for (nombre x = 0; x*x < limite + 1; ++x)
        {
            nombre y_min = 0;
            if (x*x < L)
                y_min = std::max<nombre>(arrondi(racine_carre(L - x*x), 2) + x%2 - 4, x+2);
            else
                y_min = x + 2;
                
            for (nombre y = y_min; y*y < limite - x*x + 1; y += 2)
            {
                nombre z = x*x + y*y;
                if (z >= U)
                    break;
                if (L <= z)
                    compteurs[(z - L)/2] += 1;
            }
            
        }
        
        for (nombre c : compteurs)
        {
            resultat += c*(c-1)*(c-2)/6;
        }
    }
    
    return std::to_string(resultat);
}
