#include "problemes.h"
#include "arithmetique.h"
#include "racine.h"

#include <execution>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    struct Point {
        long double x;
        long double y;

        Point(long double _x, long double _y) : x(_x), y(_y) {}

        bool operator<(const Point &p) const {
            if (std::abs(x - p.x) < std::numeric_limits<long double>::epsilon())
                return x < p.x;
            return y < p.y;
        }
    };
}

ENREGISTRER_PROBLEME(184, "Triangles containing the origin") {
    // Consider the set Ir of points (x,y) with integer co-ordinates in the interior of the circle  with radius r,
    // centered at the origin, i.e. x2 + y2 < r2.
    //
    // For a radius of 2, I2 contains the nine points (0,0), (1,0), (1,1), (0,1), (-1,1), (-1,0), (-1,-1), (0,-1) and
    // (1,-1). There are eight triangles having all three vertices in I2 which contain the origin in the interior. Two
    // of them are shown below, the others are obtained from these by rotation.
    //
    // For a radius of 3, there are 360 triangles containing the origin in the interior and having all vertices in I3
    // and for I5 the number is 10600.
    //
    // How many triangles are there containing the origin in the interior and having all three vertices in I105?
    nombre limite = 105;

    std::vector<std::pair<Point, nombre>> points;
    for (nombre x = 0; x < limite; ++x)
        for (nombre y = 1; y < limite; ++y) {
            nombre r2 = x * x + y * y;
            if (r2 > 0 && r2 < limite * limite && arithmetique::PGCD(x, y) == 1)
                points.emplace_back(Point(x, y), racine::racine_carre((limite * limite - 1) / r2));
        }

    std::sort(std::execution::par, points.begin(), points.end());

    nombre resultat = 0;
    size_t longueur = points.size();
    for (size_t i = 0; i < longueur; ++i) {
        nombre compteur = 0;
        for (size_t j = i + 1; j < i + 2 * longueur; ++j) {
            resultat += points[i].second * points[j % longueur].second * compteur;
            compteur += points[j % longueur].second;
        }
    }

    return std::to_string(resultat * 4 / 3);
}
