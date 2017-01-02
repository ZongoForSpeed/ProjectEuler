#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "grand_nombre.h"

typedef std::vector<grand_nombre> vecteur;

ENREGISTRER_PROBLEME(293, "Pseudo-Fortunate Numbers")
{
    // An even positive integer N will be called admissible, if it is a power of
    // 2 or its distinct prime factors are consecutive primes.
    // The first twelve admissible numbers are 2,4,6,8,12,16,18,24,30,32,36,48.
    //
    // If N is admissible, the smallest integer M > 1 such that N+M is prime,
    // will be called the pseudo-Fortunate number for N.
    //
    // For example, N=630 is admissible since it is even and its distinct prime
    // factors are the consecutive primes 2,3,5 and 7.
    // The next prime number after 631 is 641; hence, the pseudo-Fortunate number
    // for 630 is M=11.
    // It can also be seen that the pseudo-Fortunate number for 16 is 3.
    // 
    // Find the sum of all distinct pseudo-Fortunate numbers for admissible numbers
    // N less than 10**9.
    vecteur premiers;
    premiers::crible2<grand_nombre>(50, std::back_inserter(premiers));
    
    grand_nombre limite = grand_nombre::puissance(10, 9);
    
    vecteur fortunate;
    for (grand_nombre p = premiers.front(); p < limite; p *= premiers.front())
    {
        fortunate.push_back(p);
    }
    
    std::set<grand_nombre> pseudoFortunate;
    for (const grand_nombre & p: premiers)
    {
        vecteur suivant;
        for (grand_nombre produit = p; produit < limite; produit *= p)
        {
            for (const grand_nombre & n: fortunate)
            {
                grand_nombre f = produit*n;
                if (f >= limite)
                    break;  
                suivant.push_back(f);
            }       
            std::sort(suivant.begin(), suivant.end());
        }
        
        if (suivant.size() == 0)
            break;
            
        for (const grand_nombre & n: suivant)
        {
            grand_nombre m = (n + 1).premier_suivant() - n;
            pseudoFortunate.insert(m);
        }
            
        std::swap(fortunate, suivant);
    }

    grand_nombre resultat = 0;
    for (const grand_nombre & n: pseudoFortunate)
        resultat += n;
    
    return resultat.to_string();
}
