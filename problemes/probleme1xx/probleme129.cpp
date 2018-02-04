#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(129, "Repunit divisibility") {
    // A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit of length k;
    // for example, R(6) = 111111.
    //
    // Given that n is a positive integer and GCD(n, 10) = 1, it can be shown that there always exists a value, k, for
    // which R(k) is divisible by n, and let A(n) be the least such value of k; for example, A(7) = 6 and A(41) = 5.
    //
    // The least value of n for which A(n) first exceeds ten is 17.
    //
    // Find the least value of n for which A(n) first exceeds one-million.
    nombre limite = 1000000;
    nombre resultat = 0;
    for (nombre n = 999999;; n += 2) {
        if (n % 5 != 0) {
            nombre k = arithmetiques::repunit::A(n);

            if (k > limite) {
                std::cout << "A(" << n << ") = " << k << std::endl;
                resultat = n;
                break;
            }
        }
    }

    return std::to_string(resultat);
}

