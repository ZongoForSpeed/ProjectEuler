#include "problemes.h"
#include "chiffres.h"
#include "premiers.h"
#include "mp_nombre.h"

#include <set>

typedef std::vector<size_t> vecteur;
typedef std::pair<size_t, size_t> paire;

namespace
{
    bool test200(size_t n)
    {
        while (n != 0)
        {
            if (n%1000 == 200)
                return true;
            n /= 10;
        }
        
        return false;
    }

    bool test(size_t n)
    {
        if (!test200(n))
            return false;
            
        auto chiffres = chiffres::extraire_chiffres(n);
        for (size_t i = 0; i < chiffres.size(); ++i)
        {
            size_t c = chiffres[i];
            for (size_t a = 0; a < 10; ++a)
            {
                if (c != a)
                {
                    chiffres[i] = a;
                    if (mp_nombre::premier(chiffres::conversion_nombre<size_t>(chiffres.begin(), chiffres.end())))
                        return false;
                }
            }
            
            chiffres[i] = c;
        }
        
        return true;
    }
}

ENREGISTRER_PROBLEME(200, "Find the 200th prime-proof sqube containing the contiguous sub-string \"200\"")
{
    // We shall define a sqube to be a number of the form, p2q3, where p and q are distinct primes.
    // For example, 200 = 5²2^3 or 120072949 = 23²61^3.
    //
    // The first five squbes are 72, 108, 200, 392, and 500.
    //
    // Interestingly, 200 is also the first number for which you cannot change any single digit to 
    // make a prime; we shall call such numbers, prime-proof. The next prime-proof sqube which 
    // contains the contiguous sub-string "200" is 1992008.
    //
    // Find the 200th prime-proof sqube containing the contiguous sub-string "200".
    std::set<size_t> premiers;
    premiers::crible235<size_t>(200000, std::inserter(premiers, premiers.end()));
    
    vecteur squbes;
    for (auto p1: premiers)
    for (auto p2: premiers)
    {
        if (p1 != p2)
        {
            size_t sqube = p1*p1*p1*p2*p2;
            if ((squbes.size() < 200 || sqube < squbes.back()) && test(sqube))
            {
                if (squbes.size() == 200)
                    squbes.back() = sqube;
                else
                    squbes.push_back(sqube);
                std::sort(squbes.begin(), squbes.end());
            }
        }
    }
    
    size_t resultat = squbes.back();
    return std::to_string(resultat);
}
