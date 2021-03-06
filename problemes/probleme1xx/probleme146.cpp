#include "problemes.h"
#include "numerique.h"
#include "premiers.h"

ENREGISTRER_PROBLEME(146, "Investigating a Prime Pattern ") {
    // The smallest positive integer n for which the numbers n²+1, n²+3, n²+7, n²+9, n²+13, and n²+27 are consecutive
    // primes is 10. The sum of all such integers n below one-million is 1242490.
    //
    // What is the sum of all such integers n below 150 million?
    size_t limite = 150000000ULL;
    size_t resultat = 0;
    for (size_t n = 10; n < limite; n += 10) {
        if (size_t reste = n % 210;reste == 10 || reste == 80 || reste == 130 || reste == 200) {
            uint128_t n2 = n * n;
            uint128_t p = (n2 + 1);
            if (!premiers::miller_rabin(p))
                continue;

            p = premiers::suivant(p);
            if (p != (n2 + 3))
                continue;

            p = premiers::suivant(p);
            if (p != (n2 + 7))
                continue;

            p = premiers::suivant(p);
            if (p != (n2 + 9))
                continue;

            p = premiers::suivant(p);
            if (p != (n2 + 13))
                continue;

            p = premiers::suivant(p);
            if (p == (n2 + 27)) {
                std::cout << n << std::endl;
                resultat += n;
            }
        }
    }
    return std::to_string(resultat);
}
