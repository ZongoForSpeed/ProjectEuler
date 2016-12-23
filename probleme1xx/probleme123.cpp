#include "problemes.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(123, "Prime square remainders")
{
    // Let pn be the nth prime: 2, 3, 5, 7, 11, ..., and let r be the remainder when 
    // (pn−1)^n + (pn+1)^n is divided by pn^2.
    //
    // For example, when n = 3, p3 = 5, and 43 + 63 = 280 ≡ 5 mod 25.
    // 
    // The least value of n for which the remainder first exceeds 10^9 is 7037.
    //
    // Find the least value of n for which the remainder first exceeds 10^10.
    vecteur premiers;
    premiers::crible23<nombre>(1000000, std::back_inserter(premiers));
    
    nombre borne = puissance::puissance<nombre, unsigned>(10, 10);

    nombre resultat = 0;
    for (size_t n = 1;; ++n)
    {
        nombre pn = premiers.at(n - 1);
        nombre pnpn = pn*pn;
        nombre p1 = puissance::puissance_modulaire<nombre>(pn + 1, n, pnpn);
        nombre p2 = puissance::puissance_modulaire<nombre>(pn - 1, n, pnpn);
        if ((p1 + p2)%(pnpn) > borne)
        {
            resultat = n;
            break;
        }
    }
    
    return std::to_string(resultat);
}
