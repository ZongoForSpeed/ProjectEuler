#include "problemes.h"
#include "utilitaires.h"
#include "puissance.h"
#include "premiers.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(443, "GCD sequence") {
    // Let g(n) be a sequence defined as follows:
    // g(4) = 13,
    // g(n) = g(n-1) + gcd(n, g(n-1)) for n > 4.
    //
    // The first few values are:
    //
    // n	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	...
    // g(n)	13	14	16	17	18	27	28	29	30	31	32	33	34	51	54	55	60	...
    //
    // You are given that g(1 000) = 2524 and g(1 000 000) = 2624152.
    //
    // Find g(10**15).
    const nombre limite = puissance::puissance<nombre>(10, 15u);
    nombre n = 17;
    nombre resultat = 0;

    while (true) {
        nombre k = n - 1;
        if (!premiers::miller_rabin(2 * n - 1, 10)) {
            k = 1;
            while ((2 * n - 1) % (2 * k + 1)) {
                ++k;
            }
        }

        n += k;
        if (n > limite) {
            resultat = 2 * (n - k) + limite;
            break;
        }
    }
    return std::to_string(resultat);
}
