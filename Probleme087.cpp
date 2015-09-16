#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme087()
{
    Timer t("probleme 87");
    // The smallest number expressible as the sum of a prime square, prime cube, and prime fourth 
    // power is 28. In fact, there are exactly four numbers below fifty that can be expressed in 
    // such a way:
    //
    //  28 = 2² + 2^3 + 2^4
    //  33 = 3² + 2^3 + 2^4
    //  49 = 5² + 2^3 + 2^4
    //  47 = 2² + 3^3 + 2^4
    //
    // How many numbers below fifty million can be expressed as the sum of a prime square, prime cube,
    // and prime fourth power?
    const nombre limite = 50000000;
    vecteur premiers;
    premiers::crible23<nombre>(std::sqrt(limite) + 6, std::back_inserter(premiers));
    
    std::set<nombre> resultat;
    for (nombre p: premiers)
    {
        nombre pp = p*p*p*p;
        if (pp > limite)
            break;
        for (nombre q: premiers)
        {
            nombre qq = q*q*q + pp;
            if (qq > limite)
                break;
            for (nombre r: premiers)
            {
                nombre n = r*r + qq;
                if (n > limite)
                    break;
                resultat.insert(n);
            }
        }
    }
    
    std::cout << "Solution: " << resultat.size() << std::endl;
}
