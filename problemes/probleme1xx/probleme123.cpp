#include "problemes.h"
#include "numerique.h"
#include "premiers.h"
#include "puissance.h"

typedef std::vector<int128_t> vecteur;

ENREGISTRER_PROBLEME(123, "Prime square remainders") {
    // Let pn be the nth prime: 2, 3, 5, 7, 11, ..., and let r be the remainder when (pn−1)^n + (pn+1)^n is divided
    // by pn^2.
    //
    // For example, when n = 3, p3 = 5, and 43 + 63 = 280 ≡ 5 mod 25.
    // 
    // The least value of n for which the remainder first exceeds 10^9 is 7037.
    //
    // Find the least value of n for which the remainder first exceeds 10^10.
    vecteur premiers;
    premiers::crible23<int128_t>(1000000u, std::back_inserter(premiers));

    int128_t borne = puissance::puissance<int128_t>(10, 10u);

    int128_t resultat = 0;
    for (size_t n = 1;; ++n) {
        int128_t pn = premiers.at(n - 1);
        int128_t pnpn = pn * pn;
        int128_t p1 = puissance::puissance_modulaire<int128_t>(pn + 1, n, pnpn);
        int128_t p2 = puissance::puissance_modulaire<int128_t>(pn - 1, n, pnpn);
        if ((p1 + p2) % (pnpn) > borne) {
            resultat = n;
            break;
        }
    }

    return std::to_string(resultat);
}
