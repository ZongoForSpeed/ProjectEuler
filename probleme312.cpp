#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "premiers.h"

#include <iostream>

typedef size_t nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre Sierpinski(nombre ordre, nombre n, nombre m, const vecteur & phi)
    {
        // C(n) = 2**(3**(n−2)) * 3**(3**(n−2)−3)/2
        if (ordre == 0)
            return n%phi[m];
        
        nombre suivant = Sierpinski(ordre - 1, n, m + 2, phi);
        nombre tmp = puissance::puissance_modulaire<nombre>(3, suivant - 2, phi[m + 1]);
        return puissance::puissance_modulaire<nombre>(2, tmp, phi[m]) 
            * puissance::puissance_modulaire<nombre>(3, (tmp-3)/2, phi[m]) % phi[m];
    }
}

ENREGISTRER_PROBLEME(312, "Cyclic paths on Sierpiński graphs")
{
    // - A Sierpiński graph of order-1 (S1) is an equilateral triangle.
    // - Sn+1 is obtained from Sn by positioning three copies of Sn so that every
    // pair of copies has one common corner.
    //
    // Let C(n) be the number of cycles that pass exactly once through all the 
    // vertices of Sn.
    // For example, C(3) = 8 because eight such cycles can be drawn on S3, as 
    // shown below:
    //
    // It can also be verified that :
    // C(1) = C(2) = 1
    // C(5) = 71328803586048
    // C(10 000) mod 10**8 = 37652224
    // C(10 000) mod 13**8 = 617720485
    //
    // Find C(C(C(10 000))) mod 13**8.
    nombre modulo = puissance::puissance<nombre>(13, 8);
    vecteur premiers;
    premiers::crible235<nombre>(modulo, std::back_inserter(premiers));
    
    vecteur phi { modulo };
    while (phi.size() < 10)
    {
        phi.push_back(arithmetiques::phi(phi.back(), premiers));
    }
    
    nombre resultat = Sierpinski(3, 10000, 0, phi);
    return std::to_string(resultat);
}
