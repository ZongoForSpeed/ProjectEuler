#include "problemes.h"

ENREGISTRER_PROBLEME(216, "Investigating the primality of numbers of the form 2n²-1") {
    // Consider numbers t(n) of the form t(n) = 2n²-1 with n > 1.
    // The first such numbers are 7, 17, 31, 49, 71, 97, 127 and 161.
    // It turns out that only 49 = 7*7 and 161 = 7*23 are not prime.
    // For n ≤ 10000 there are 2202 numbers t(n) that are prime.
    // 
    // How many numbers t(n) are prime for n ≤ 50,000,000 ?
    size_t limite = 50000000;
    size_t resultat = 0;

    std::vector<size_t> p(limite + 1, 0);
    for (size_t n = 0; n < limite + 1; ++n) {
        p[n] = 2 * n * n - 1;
    }

    for (size_t n = 2; n <= limite; n++) {
        size_t t = p[n];
        if (t == 1) continue;
        if (t == 2 * n * n - 1) {
            ++resultat;
        }

        for (size_t k = 1;; ++k) {
            size_t i = t * k - n;
            if (i > limite)
                break;
            while (p[i] % t == 0) {
                p[i] /= t;
            }
        }

        for (size_t k = 1;; k++) {
            size_t i = t * k + n;
            if (i > limite)
                break;
            while (p[i] % t == 0) {
                p[i] /= t;
            }
        }
    }

    return std::to_string(resultat);
}
