#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "mpz_nombre.h"

typedef std::vector<mpz_nombre> vecteur;

ENREGISTRER_PROBLEME(266, "Pseudo Square Root") {
    // The divisors of 12 are: 1,2,3,4,6 and 12.
    // 
    // The largest divisor of 12 that does not exceed the square root of 12 is 3. We shall call the largest divisor of
    // an integer n that does not exceed the square root of n the pseudo square root (PSR) of n.
    // It can be seen that PSR(3102)=47.
    //
    // Let p be the product of the primes below 190.
    // Find PSR(p) mod 10^16.
    const mpz_nombre modulo = mpz_nombre::puissance(10, 16);
    vecteur premiers;
    premiers::crible2<mpz_nombre>(190, std::back_inserter(premiers));

    mpz_nombre p1 = 1;
    for (size_t n = 0; n < premiers.size() / 2; ++n)
        p1 *= premiers[n];
    auto d1 = arithmetique::diviseurs(p1, premiers);

    mpz_nombre p2 = 1;
    for (size_t n = premiers.size() / 2; n < premiers.size(); ++n)
        p2 *= premiers[n];
    auto d2 = arithmetique::diviseurs(p2, premiers);

    mpz_nombre resultat = 0;

    auto it1 = d1.begin();
    auto it2 = d2.rbegin();
    while (it1 != d1.end() && it2 != d2.rend()) {
        mpz_nombre courant = (*it1) * (*it2);
        if (courant * courant > p1 * p2)
            ++it2;
        else {
            resultat = std::max(resultat, courant);
            ++it1;
        }
    }

    resultat %= modulo;
    return resultat.to_string();
}
