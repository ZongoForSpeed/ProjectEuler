#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    std::pair<nombre, nombre> fibonacci_(nombre n) {
        if (n == 0)
            return std::make_pair(1, 0);

        auto[fk_1, fk] = fibonacci_(n / 2);

        if (n % 2 == 0)
            return std::make_pair(fk * fk + fk_1 * fk_1, fk * (2 * fk_1 + fk));
        else
            return std::make_pair(fk * (2 * fk_1 + fk), (fk_1 + fk) * (fk_1 + fk) + fk * fk);
    }

    nombre fibonacci(nombre n) {
        return fibonacci_(n).second;
    }
}

ENREGISTRER_PROBLEME(138, "Special isosceles triangles") {
    // Consider the isosceles triangle with base length, b = 16, and legs, L = 17.
    //
    // By using the Pythagorean theorem it can be seen that the height of the triangle, h = √(172 − 82) = 15, which is
    // one less than the base length.
    // 
    // With b = 272 and L = 305, we get h = 273, which is one more than the base length, and this is the second smallest
    // isosceles triangle with the property that h = b ± 1.
    //
    // Find ∑ L for the twelve smallest isosceles triangles for which h = b ± 1 and b, L are positive integers.
    nombre objectif = 12;
    nombre resultat = 0;

    for (nombre n = 1; n < objectif + 1; ++n) {
        resultat += fibonacci(6 * n + 3) / 2;
    }

    return std::to_string(resultat);
}

