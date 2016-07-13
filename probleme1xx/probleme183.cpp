#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

namespace
{
    bool infini(nombre n, nombre k)
    {
        k /= arithmetiques::PGCD(n, k);
        while (k%2 == 0)
            k /= 2;
        
        while (k%5 == 0)
            k /= 5;
            
        return k == 1;
    }
    
    bool terminating(nombre n)
    {
        long double k0 = n / M_E;
        nombre k_max = static_cast<nombre>(std::ceil(k0));
        nombre k_min = static_cast<nombre>(std::floor(k0));

        long double p_max = puissance::puissance(n / std::ceil(k0), k_max);
        long double p_min = puissance::puissance(n / std::floor(k0), k_min);
        
        if (p_max > p_min)
            return infini(n, k_max);
        else
            return infini(n, k_min);
    }
}

ENREGISTRER_PROBLEME(183, "Maximum product of parts")
{
    // Let N be a positive integer and let N be split into k equal parts, r = N/k, so that N = r + r + ... + r.
    // Let P be the product of these parts, P = r × r × ... × r = rk.
    //
    // For example, if 11 is split into five equal parts, 11 = 2.2 + 2.2 + 2.2 + 2.2 + 2.2, 
    // then P = 2.25 = 51.53632.
    //
    // Let M(N) = Pmax for a given value of N.
    //
    // It turns out that the maximum for N = 11 is found by splitting eleven into four equal parts
    // which leads to Pmax = (11/4)4; that is, M(11) = 14641/256 = 57.19140625, which is a terminating decimal.
    //
    // However, for N = 8 the maximum is achieved by splitting it into three equal parts, so M(8) = 512/27,
    // which is a non-terminating decimal.
    //
    // Let D(N) = N if M(N) is a non-terminating decimal and D(N) = -N if M(N) is a terminating decimal.
    //
    // For example, ΣD(N) for 5 ≤ N ≤ 100 is 2438.
    //
    // Find ΣD(N) for 5 ≤ N ≤ 10000.
    nombre limite = 10000;
    // std::cout << std::boolalpha;
    // std::cout << "terminating(8) = " << terminating(8) << std::endl;
    // std::cout << "terminating(11) = " << terminating(11) << std::endl;
    
    nombre resultat_positif = 0;
    nombre resultat_negatif = 0;
    for (nombre n = 5; n < limite + 1; ++n)
    {
        if (terminating(n))
            resultat_negatif += n;
        else
            resultat_positif += n;
    }

    return std::to_string(resultat_positif - resultat_negatif);
}
