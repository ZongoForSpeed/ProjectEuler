#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"

#include <iostream>
#include <vector>
#include <list>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(21, "Amicable numbers")
{
    // Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
    // If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
    // 
    // For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
    // 
    // Evaluate the sum of all the amicable numbers under 10000.
    std::vector<nombre> premiers;
    premiers::crible235<nombre>(10000, std::back_inserter(premiers));
    vecteur diviseurs;
    diviseurs.reserve(10000);
    diviseurs.push_back(0);
    nombre resultat = 0;
    for (nombre n = 1; n < 10000; ++n)
    {
        nombre d = arithmetiques::somme_diviseurs(n, premiers) - n;
        diviseurs.push_back(d);
        if (d < n && diviseurs[d] == n)
        {
            resultat += d + n;
        }
    }
    return std::to_string(resultat);
}
