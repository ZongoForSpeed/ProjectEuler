#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "utilitaires.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double f(nombre xa, nombre xb) {
        // Wolfram alpha
        return static_cast<long double>(-std::sqrt((static_cast<double>(-(xa * xa)) + 2 * std::sqrt(
                xa * xa * xa * xa + 2 * xa * xa * xa * xb - 10 * xa * xa * xa + 3 * xa * xa * xb * xb
                - 50 * xa * xa * xb + 125 * xa * xa + 2 * xa * xb * xb * xb - 50 * xa * xb * xb
                + 300 * xa * xb - 500 * xa + xb * xb * xb * xb - 10 * xb * xb * xb
                + 125 * xb * xb - 500 * xb + 625) + static_cast<double>(2 * xa * xb) - static_cast<double>(10 * xa) +
                                                    static_cast<double>(2 * xb * xb) - static_cast<double>(10 * xb) + 25) / 3));
    }

    template<typename N>
    N norme(N x, N y) {
        return x * x + y * y;
    }

    long double perimetre(nombre xa, nombre ya, nombre xb, nombre yb, nombre xc, nombre yc) {
        return std::hypot(1.0L * xa - xb, ya - yb)
               + std::hypot(1.0L * xa - xc, ya - yc)
               + std::hypot(1.0L * xb - xc, yb - yc);
    }
}

ENREGISTRER_PROBLEME(264, "Triangle Centres") {
    // Consider all the triangles having:
    //
    // All their vertices on lattice points.
    // Circumcentre at the origin O.
    // Orthocentre at the point H(5, 0).
    // There are nine such triangles having a perimeter ≤ 50.
    // Listed and shown in ascending order of their perimeter, they are:
    //
    //      A(-4, 3), B(5, 0), C(4, -3)
    //      A(4, 3), B(5, 0), C(-4, -3)
    //      A(-3, 4), B(5, 0), C(3, -4)
    //
    //      A(3, 4), B(5, 0), C(-3, -4)
    //      A(0, 5), B(5, 0), C(0, -5)
    //      A(1, 8), B(8, -1), C(-4, -7)
    //
    //      A(8, 1), B(1, -8), C(-4, 7)
    //      A(2, 9), B(9, -2), C(-6, -7)
    //      A(9, 2), B(2, -9), C(-6, 7)
    // 
    // The sum of their perimeters, rounded to four decimal places, is 291.0089.
    //
    // Find all such triangles with a perimeter ≤ 10^5.
    // Enter as your answer the sum of their perimeters rounded to four decimal places.
    long double limite = 100000.0L;

    // xa² + ya² = xb² + yb² = xc² + yc², xa + xb + xc = 5, ya + yb + yc = 0
    long double resultat = 0;
    nombre gr = 16000;
    for (nombre xa = 0; xa + gr > 0; --xa)
        for (nombre xb = xa; xb <= (-xa + 5) / 2; ++xb) {
            long double fya = f(xa, xb);
            if (std::abs(fya - std::round(fya)) < std::numeric_limits<long double>::epsilon()) {
                auto ya = static_cast<nombre>(fya);
                auto fyb = static_cast<long double>(std::sqrt(xa * xa + ya * ya - xb * xb));
                if (std::abs(fyb - std::round(fyb)) < std::numeric_limits<long double>::epsilon()) {
                    auto yb = static_cast<nombre>(fyb);
                    nombre yc = -ya - yb;
                    nombre xc = -xa - xb + 5;
                    long double p = perimetre(xa, ya, xb, yb, xc, yc);
                    if (norme(xa, ya) == norme(xb, yb) && norme(xb, yb) == norme(xc, yc) && p <= limite)
                        if ((xa != xb || ya != yb) && (xc != xb || yc != yb) && (xa != xc || ya != yc)) {
                            if ((xa == xb && ya == -yb && yc == 0) || (xb == xc && yb == -yc && ya == 0))
                                resultat += p;
                            else
                                resultat += 2 * p;
                        }
                }
            }
        }

    return format::to_fixed(resultat, 4);
}
