#include "problemes.h"
#include "arithmetique.h"
#include "racine.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(390, "Triangles with non rational sides and integral area") {
    // Consider the triangle with sides √5, √65 and √68. It can be shown that this triangle has area 9.
    //
    // S(n) is the sum of the areas of all triangles with sides √(1+b2), √(1+c2) and √(b2+c2) (for positive integers b
    // and c ) that have an integral area not exceeding n.
    //
    // The example triangle has b=2 and c=8.
    //
    // S(10^6) = 18018206.
    //
    // Find S(10^10).
    const nombre limite = 20'000'000'000ULL;

    nombre resultat = 0;
    for (nombre a = 2; a * a + 1 <= limite; a += 2) {
        nombre max_t = limite / (a * a + 1);
        for (nombre t = 2; t <= max_t; t += 2) {
            nombre s = a * a * t * t - a * a + t * t;
            auto v = racine::racine_carre<nombre>(s);
            if (v * v == s) {
                nombre b = a * t + v;
                nombre n = a * b + t;
                if (n > limite)
                    break;
                resultat += n / 2;
            }
        }
    }
    return std::to_string(resultat);
}
