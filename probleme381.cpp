#include "problemes.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <set>
#include <deque>
#include <boost/multiprecision/gmp.hpp>
typedef boost::multiprecision::mpz_int nombre;

namespace
{
    nombre S(size_t p)
    {
        if (p < 5)
            return 0;
        
        size_t f = p - 1;
        // std::cout << p - 1 << "! mod " << p << " = " << f << std::endl;
        nombre resultat = f;
        for (size_t n = 2; n < 6; ++n)
        {
            f *= puissance::puissance_modulaire(p - n + 1, p - 2, p);
            f %= p;
            // std::cout << p - n << "! mod " << p << " = " << f << std::endl;
            resultat += f;
        }
        
        return resultat % p;
    }
}

ENREGISTRER_PROBLEME(381, "(prime-k) factorial")
{
    // For a prime p let S(p) = (Sum(p-k)!) mod(p) for 1 ≤ k ≤ 5.
    //
    // For example, if p=7,
    // (7-1)! + (7-2)! + (7-3)! + (7-4)! + (7-5)! = 6! + 5! + 4! + 3! + 2! = 720+120+24+6+2 = 872.
    // As 872 mod(7) = 4, S(7) = 4.
    //
    // It can be verified that Sum S(p) = 480 for 5 ≤ p < 100.
    //
    // Find SumS(p) for 5 ≤ p < 10^8.
    size_t limite = 100000000L;
    
    std::deque<size_t> premiers;
    premiers::crible2<size_t>(limite, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for (const size_t & p : premiers)
    {
        resultat += S(p);                
    }
    
    return std::to_string(resultat);
}
