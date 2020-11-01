#include <numeric>
#include "problemes.h"
#include "utilitaires.h"
#include "puissance.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(346, "Strong Repunits") {
    // The number 7 is special, because 7 is 111 written in base 2, and 11 written in base 6
    //  (i.e. 710 = 116 = 1112). In other words, 7 is a repunit in at least two bases b > 1.
    //
    // We shall call a positive integer with this property a strong repunit. It can be verified that there are 8 strong
    // repunits below 50: {1,7,13,15,21,31,40,43}.
    // Furthermore, the sum of all strong repunits below 10**00 equals 15864.
    // Find the sum of all strong repunits below 10**12.
    nombre limite = puissance::puissance<nombre>(10, 12);

    std::set<nombre> ensemble;
    ensemble.insert(1);
    for (nombre base = 2; base * base + base + 1 <= limite; ++base) {
        nombre repunit = base * base + base + 1;
        while (repunit <= limite) {
            ensemble.insert(repunit);
            repunit = repunit * base + 1;
        }
    }
    nombre somme = std::reduce(ensemble.begin(), ensemble.end());
    return somme.str();
}
