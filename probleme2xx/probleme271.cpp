#include "problemes.h"
#include "arithmetiques.h"
#include "nombre.h"

typedef std::vector<nombre> vecteur;

namespace
{
    nombre S(nombre n)
    {
        nombre somme = 0;
        nombre increment = 2*3*5*11*17*23*29*41;
        
        for (nombre x = increment + 1; x < n; x += increment)
        {
            nombre x3 = x*x*x;
            if (x3 % n == 1)
                somme += x;
        }
        
        return somme;
    }
}

ENREGISTRER_PROBLEME(271, "Modular Cubes, part 1")
{
    // For a positive number n, define S(n) as the sum of the integers x, for 
    // which 1<x<n and x3≡1 mod n.
    //
    // When n=91, there are 8 possible values for x, namely : 9, 16, 22, 29, 53,
    // 74, 79, 81.
    // Thus, S(91)=9+16+22+29+53+74+79+81=363.
    //
    // Find S(13082761331670030).
    nombre n = 13082761331670030ULL;
    nombre resultat = S(n);
    return resultat.to_string();
}
