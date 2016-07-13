#include "problemes.h"
#include "premiers.h"

#include <iostream>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(278, "Linear Combinations of Semiprimes")
{
    // Given the values of integers 1 < a1 < a2 <... < an, consider the linear 
    // combination q1.a1 + q2.a2 + ... + qn.an = b, using only integer values 
    // qk ≥ 0.
    //
    // Note that for a given set of ak, it may be that not all values of b are 
    // possible. 
    // For instance, if a1 = 5 and a2 = 7, there are no q1 ≥ 0 and q2 ≥ 0 such 
    // that b could be 1, 2, 3, 4, 6, 8, 9, 11, 13, 16, 18 or 23. 
    // 
    // In fact, 23 is the largest impossible value of b for a1 = 5 and a2 = 7.
    // We therefore call f(5, 7) = 23.
    //
    // Similarly, it can be shown that f(6, 10, 15)=29 and f(14, 22, 77) = 195.
    //
    // Find ∑ f(p*q,p*r,q*r), where p, q and r are prime numbers and p < q < r < 5000.
    vecteur premiers;
    premiers::crible<nombre>(5000, std::back_inserter(premiers));
    
    nombre resultat = 0;

    for (auto it1 = premiers.begin(), en = premiers.end(); it1 != en; ++it1)
    for (auto it2 = std::next(it1); it2 != en; ++it2)
    for (auto it3 = std::next(it2); it3 != en; ++it3)
    {
        const nombre p = *it1;
        const nombre q = *it2;
        const nombre r = *it3;
        // https://fr.wikipedia.org/wiki/Probl%C3%A8me_des_pi%C3%A8ces_de_monnaie
        resultat += p * q * r * 2 - p * q - q * r - p * r;
    }
    
    return std::to_string(resultat);
}
