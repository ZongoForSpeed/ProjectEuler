#include "problemes.h"

ENREGISTRER_PROBLEME(291, "Panaitopol Primes") {
    // A prime number p is called a Panaitopol prime if (x**4 - y**4)/(x**3 + y**3) for some positive integers x and y.
    //
    // Find how many Panaitopol primes are less than 5×10**15.
    size_t limite = 50000000;

    std::vector<size_t> dp(limite + 1, 0);
    for (size_t i = 0; i < limite + 1; ++i) {
        dp[i] = 2 * i * i + 2 * i + 1;
    }

    size_t resultat = 0;
    for (size_t i = 1; i < limite; i++) {
        if (dp[i] == 2ll * i * i + 2 * i + 1) {
            resultat++;
        }
        if (dp[i] > 1) {
            size_t p = dp[i];
            for (size_t j = i; j < limite; j += p) {
                while (dp[j] % p == 0) dp[j] /= p;
            }
            for (size_t j = p - 1 - i; j < limite; j += p) {
                while (dp[j] % p == 0) dp[j] /= p;
            }
        }
    }

    return std::to_string(resultat);
}
