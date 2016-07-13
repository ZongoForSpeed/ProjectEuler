#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(217, "Balanced Numbers")
{
    // A positive integer with k (decimal) digits is called balanced if its first [k/2] digits sum
    // to the same value as its last [k/2] digits, where ⌈x⌉, pronounced ceiling of x, is the smallest
    // integer ≥ x, thus [π] = 4 and [5] = 5.
    //
    // So, for example, all palindromes are balanced, as is 13722.
    //
    // Let T(n) be the sum of all balanced numbers less than 10n. 
    // Thus: T(1) = 45, T(2) = 540 and T(5) = 334795890.
    //
    // Find T(47) mod 3^15
    nombre masque = puissance::puissance(3, 15);
    nombre limite = 47;
    
    typedef std::map<nombre, std::map<nombre, nombre>> dictionnaire;
    dictionnaire T_somme;
    dictionnaire T_compteur;
    
    T_somme[0][0] = 0;
    T_compteur[0][0] = 1;
    T_somme[1][0] = 45;
    T_compteur[1][0] = 10;

    nombre resultat = T_somme[1][0];

    for (unsigned short n = 2; n <= limite; ++n)
    {
        auto & somme = T_somme[n];
        auto & compteur = T_compteur[n];
        
        nombre p10 = puissance::puissance<nombre>(10, n - 1);
        
        for (short c1 = 0; c1 < 10; ++c1)
        for (short c2 = 0; c2 < 10; ++c2)
        {
            for (auto t: T_somme[n - 2])
            {
                nombre d = t.first + c1 - c2;
                nombre c = T_compteur[n - 2][t.first];
                compteur[d] += c;
                nombre s = t.second*10 + c*(c1*p10 + c2);
                somme[d] += s;
                if (c1 != 0 && d == 0)
                    resultat += s;
            }
        }
    }

    return std::to_string(resultat%masque);
}
