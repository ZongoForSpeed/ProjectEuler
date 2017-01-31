#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"
#include "mp_nombre.h"

typedef std::vector<mp_nombre> vecteur;

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
    premiers::crible23<mp_nombre>(1000000, std::back_inserter(premiers));
    
    mp_nombre borne = mp_nombre::puissance(10, 10);

    mp_nombre resultat = 0;
    for (size_t n = 1;; ++n)
    {
        mp_nombre pn = premiers.at(n - 1);
        mp_nombre pnpn = pn*pn;
        mp_nombre p1 = mp_nombre::puissance_modulaire(pn + 1, n, pnpn);
        mp_nombre p2 = mp_nombre::puissance_modulaire(pn - 1, n, pnpn);
        if ((p1 + p2)%(pnpn) > borne)
        {
            resultat = n;
            break;
        }
    }
    
    return resultat.to_string();
}
