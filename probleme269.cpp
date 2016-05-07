#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre algorithme( const vecteur & residue, nombre nbChiffres )
    {
        static std::map<std::pair<vecteur, nombre>, nombre> cache;
        
        auto key = std::make_pair(residue, nbChiffres);
        auto it = cache.find(key);
        
        if (it != cache.end())
            return it->second;
            
        nombre resultat = 0;
        if (nbChiffres == 0)
        {
            if (std::find(residue.begin(), residue.end(), 0) != residue.end())
                resultat = 1;
        }
        else for (nombre chiffre = 0; chiffre < 10; ++chiffre)
        {
            vecteur _residue(10, 0);
            for (unsigned short i = 0; i < 10; ++i)
            {
                _residue[i] = chiffre - residue[i] * i;
                nombre residue_max = _residue[i] * (1-i*i);
                if (i > 1 && (8 < residue_max || residue_max < -9*i)) 
                    _residue[i] = std::numeric_limits<unsigned short>::max();
            }
            resultat += algorithme(_residue, nbChiffres - 1);
        }
        
        return cache[key] = resultat;
    }
}

ENREGISTRER_PROBLEME(269, "Polynomials with at least one integer root")
{
    // A root or zero of a polynomial P(x) is a solution to the equation P(x) = 0. 
    // Define Pn as the polynomial whose coefficients are the digits of n.
    // For example, P5703(x) = 5x**3 + 7x² + 3.
    //
    // We can see that:
    //
    //      Pn(0) is the last digit of n,
    //      Pn(1) is the sum of the digits of n,
    //      Pn(10) is n itself.
    // 
    // Define Z(k) as the number of positive integers, n, not exceeding k for 
    // which the polynomial Pn has at least one integer root.
    // 
    // It can be verified that Z(100 000) is 14696.
    //
    // What is Z(10**16)?
    vecteur residue(10, 0);
    nombre resultat = algorithme(residue, 16);
    std::cout << "Solution: " << resultat << std::endl;
}
