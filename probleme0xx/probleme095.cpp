#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(95, "Amicable chains")
{
    // The proper divisors of a number are all the divisors excluding the number itself. For example, 
    // the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28,
    // we call it a perfect number.
    //
    // Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors
    // of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284 are called an 
    // amicable pair.
    // 
    // Perhaps less well known are longer chains. For example, starting with 12496, we form a chain 
    // of five numbers:
    // 
    //                  12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)
    //
    // Since this chain returns to its starting point, it is called an amicable chain.
    // 
    // Find the smallest member of the longest amicable chain with no element exceeding one million.
    nombre limite = 1000000;

    vecteur premiers;
    premiers::crible23<nombre>(limite, std::back_inserter(premiers));
    
    vecteur somme_diviseurs(limite, 0);
    for (nombre n = 2; n < limite; ++n)
    {
        somme_diviseurs[n] = arithmetiques::somme_diviseurs(n, premiers) - n;
    }
    
    nombre maximum = 0;
    nombre resultat = 0;
    for (nombre n = 2; n < limite; ++n)
    {
        nombre s = n;
        std::set<nombre> chaine;
        do
        {
            chaine.insert(s);
            s = somme_diviseurs[s];
        }
        while(chaine.find(s) == chaine.end() && s < limite);

        if (s == n && chaine.size() > maximum)
        {
            maximum = chaine.size();
            resultat = n;
        }
    }

    return std::to_string(resultat);
}
