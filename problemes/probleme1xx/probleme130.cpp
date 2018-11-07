#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(130, "Composites with prime repunit property") {
    // A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit of length k; for
    // example, R(6) = 111111.
    //
    // Given that n is a positive integer and GCD(n, 10) = 1, it can be shown that there always exists a value, k, for
    // which R(k) is divisible by n, and let A(n) be the least such value of k; for example, A(7) = 6 and A(41) = 5.
    //
    // You are given that for all primes, p > 5, that p − 1 is divisible by A(p). For example, when p = 41, A(41) = 5,
    // and 40 is divisible by 5.
    // 
    // However, there are rare composite values for which this is also true; the first five examples being 91, 259, 451,
    // 481, and 703.
    //
    // Find the sum of the first twenty-five composite values of n for which
    // GCD(n, 10) = 1 and n − 1 is divisible by A(n).
    std::set<nombre> premiers;
    premiers::crible235<nombre>(1000000ULL, std::inserter(premiers, premiers.begin()));

    nombre limite = 25;
    nombre resultat = 0;
    nombre compteur = 0;
    for (nombre n = 1;; n += 2) {
        if (n % 5 != 0) {
            nombre k = arithmetique::repunit::A(n);

            if (n % k == 1 && premiers.find(n) == premiers.end()) {
                resultat += n;
                ++compteur;

                if (compteur >= limite)
                    break;
            }
        }
    }

    return std::to_string(resultat);
}

