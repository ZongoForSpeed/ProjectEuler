#include "../problemes.h"
#include "puissance.h"
#include "mpz_nombre.h"

#include <numeric>
#include <set>

ENREGISTRER_PROBLEME(346, "Strong Repunits") {
    // The number 7 is special, because 7 is 111 written in base 2, and 11 written in base 6
    //  (i.e. 710 = 116 = 1112). In other words, 7 is a repunit in at least two bases b > 1.
    //
    // We shall call a positive integer with this property a strong repunit. It can be verified that there are 8 strong
    // repunits below 50: {1,7,13,15,21,31,40,43}.
    // Furthermore, the sum of all strong repunits below 10**00 equals 15864.
    // Find the sum of all strong repunits below 10**12.
    mpz_nombre limite = mpz_nombre::puissance(10, 12);

    std::set<mpz_nombre> ensemble;
    ensemble.emplace(1);
    for (mpz_nombre base = 2; base * base + base + 1 <= limite; ++base) {
        mpz_nombre repunit = base * base + base + 1;
        while (repunit <= limite) {
            ensemble.emplace(repunit);
            repunit = repunit * base + 1;
        }
    }
    mpz_nombre somme = std::reduce(ensemble.begin(), ensemble.end());
    return somme.to_string();
}
