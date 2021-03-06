#include "problemes.h"
#include "arithmetique.h"
#include "racine.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

namespace {
    long double aire(long double a, long double b, long double c) {
        // Aire = sqrt((a+b+c)(-a+b+c)(a-b+c)(a+b-c)) / 4.
        return std::sqrt((a + b + c) * (b + c - a) * (a + c - b) * (a + b - c)) / 4.0L;
    }
}

ENREGISTRER_PROBLEME(195, "Inscribed circles of triangles with one angle of 60 degrees") {
    // Let's call an integer sided triangle with exactly one angle of 60 degrees a 60-degree triangle.
    // Let r be the radius of the inscribed circle of such a 60-degree triangle.
    //
    // There are 1234 60-degree triangles for which r ≤ 100.
    // Let T(n) be the number of 60-degree triangles for which r ≤ n, so
    // T(100) = 1234,  T(1000) = 22767, and  T(10000) = 359912.
    //
    // Find T(1053779).
    nombre limite = 1053779;
    nombre borne = 2 * racine::racine_carre(limite);

    // a = m² - mn + n² 
    // b = 2mn - n² 
    // c = m² - n²
    // 0 < 2*n < m
    nombre resultat = 0;
    std::cout << std::boolalpha;
    for (nombre n = 1; n < borne; ++n) {
        for (nombre m = 2 * n + 1;; ++m) {
            if (arithmetique::PGCD(m, n) == 1) {
                nombre a = m * m - m * n + n * n;
                nombre b = 2 * m * n - n * n;
                nombre c = m * m - n * n;
                nombre pgcd = arithmetique::PGCD(a, arithmetique::PGCD(b, c));
                a /= pgcd;
                b /= pgcd;
                c /= pgcd;
                // r = 2.S / (a+b+c)
                long double r = 2 * aire(a, b, c) / (a + b + c);
                if (r > 3 * limite)
                    break;

                if (r < limite) {
                    resultat += static_cast<nombre>(std::floor(limite / r));
                }
            }
        }
    }


    return std::to_string(resultat);
}
