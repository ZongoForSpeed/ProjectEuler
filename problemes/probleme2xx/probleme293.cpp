#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "mpz_nombre.h"

typedef std::vector<mpz_nombre> vecteur;

ENREGISTRER_PROBLEME(293, "Pseudo-Fortunate Numbers") {
    // An even positive integer N will be called admissible, if it is a power of 2 or its distinct prime factors are
    // consecutive primes. The first twelve admissible numbers are 2,4,6,8,12,16,18,24,30,32,36,48.
    //
    // If N is admissible, the smallest integer M > 1 such that N+M is prime, will be called the pseudo-Fortunate number
    // for N.
    //
    // For example, N=630 is admissible since it is even and its distinct prime factors are the consecutive primes 2,3,5
    // and 7. The next prime number after 631 is 641; hence, the pseudo-Fortunate number for 630 is M=11. It can also be
    // seen that the pseudo-Fortunate number for 16 is 3.
    // 
    // Find the sum of all distinct pseudo-Fortunate numbers for admissible numbers N less than 10**9.
    vecteur premiers;
    premiers::crible2<mpz_nombre>(50, std::back_inserter(premiers));

    mpz_nombre limite = mpz_nombre::puissance(10, 9);

    vecteur fortunate;
    for (mpz_nombre p = premiers.front(); p < limite; p *= premiers.front()) {
        fortunate.emplace_back(p);
    }

    std::set<mpz_nombre> pseudoFortunate;
    for (const mpz_nombre &p: premiers) {
        vecteur suivant;
        for (mpz_nombre produit = p; produit < limite; produit *= p) {
            for (const mpz_nombre &n: fortunate) {
                mpz_nombre f = produit * n;
                if (f >= limite)
                    break;
                suivant.emplace_back(f);
            }
        }

        if (suivant.empty())
            break;

        std::sort(suivant.begin(), suivant.end());

        for (const mpz_nombre &n: suivant) {
            mpz_nombre m = mpz_nombre::premier_suivant(n + 1) - n;
            pseudoFortunate.emplace(m);
        }

        std::swap(fortunate, suivant);
    }

    mpz_nombre resultat = std::reduce(pseudoFortunate.begin(), pseudoFortunate.end());

    return resultat.to_string();
}
