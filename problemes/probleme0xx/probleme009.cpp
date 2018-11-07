#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;

namespace {
    nombre Pythagorean(nombre limite) {
        for (nombre a = 1; a < limite / 3; ++a) {
            for (nombre b = a + 1; b < limite / 2; ++b) {
                nombre c = limite - a - b;
                if (a * a + b * b == c * c)
                    return a * b * c;
            }
        }

        return 0;
    }
}

ENREGISTRER_PROBLEME(9, "Special Pythagorean triplet") {
    // A Pythagorean triplet is a set of three natural numbers, a < b < c, for which, a² + b² = c²
    // For example, 3² + 4² = 9 + 16 = 25 = 5².
    //
    // There exists exactly one Pythagorean triplet for which a + b + c = 1000.
    // Find the product abc.
    nombre resultat = Pythagorean(1000);
    return std::to_string(resultat);
}
