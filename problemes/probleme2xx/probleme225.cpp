#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;

namespace {
    bool test(nombre n) {
        nombre t1 = 1;
        nombre t2 = 1;
        nombre t3 = 3;

        while (true) {
            nombre s = (t1 + t2 + t3) % n;
            t1 = t2;
            t2 = t3;
            t3 = s;

            if (t1 * t2 * t3 == 0)
                return false;
            else if (t1 * t2 * t3 == 1)
                return true;
        }
    }
}

ENREGISTRER_PROBLEME(225, "Tribonacci non-divisors") {
    // The sequence 1, 1, 1, 3, 5, 9, 17, 31, 57, 105, 193, 355, 653, 1201 ... is defined by T1 = T2 = T3 = 1 and
    // Tn = Tn-1 + Tn-2 + Tn-3.
    //
    // It can be shown that 27 does not divide any terms of this sequence.
    // In fact, 27 is the first odd number with this property.
    //
    // Find the 124th odd number that does not divide any terms of the above sequence.
    const nombre taille = 124;
    nombre compteur = 0;
    nombre resultat = 0;
    for (nombre p = 27; compteur < taille; p += 2) {
        if (test(p)) {
            // std::cout << compteur << "\t" << p << std::endl;
            resultat = p;
            ++compteur;
        }
    }

    return std::to_string(resultat);
}
