#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool lenticular(nombre x, nombre y, nombre a, nombre b) {
        nombre r = x * x + y * y;
        for (nombre v = 1; v < b; ++v) {
            nombre u = v * a / b;
            if ((x - u) * (x - u) + (y + v) * (y + v) < r)
                return false;
        }

        return true;
    }

    std::pair<nombre, nombre> diophantienne(nombre a, nombre b, nombre c) {
        // Résolution de l'equation ax + by = c
        nombre u, v;
        arithmetiques::Bezout(a, b, u, v);

        u *= c;
        v *= -c;

        nombre p = std::min((u - a) / b, v / a);

        u -= p * b;
        v -= p * a;

        return std::make_pair(u, v);
    }
}

ENREGISTRER_PROBLEME(295, "Lenticular holes") {
    // We call the convex area enclosed by two circles a lenticular hole if:
    //
    //      - The centres of both circles are on lattice points.
    //      - The two circles intersect at two distinct lattice points.
    //      - The interior of the convex area enclosed by both circles does not contain any lattice points.
    //
    // Consider the circles:
    // C0: x²+y²=25
    // C1: (x+4)²+(y-4)²=1
    // C2: (x-12)²+(y-4)²=65
    //
    // The circles C0, C1 and C2 are drawn in the picture below.
    //
    // C0 and C1 form a lenticular hole, as well as C0 and C2.
    //
    // We call an ordered pair of positive real numbers (r1, r2) a lenticular pair if there exist two circles with radii
    // r1 and r2 that form a lenticular hole. We can verify that (1, 5) and (5, √65) are the lenticular pairs of the
    // example above.
    //
    // Let L(N) be the number of distinct lenticular pairs (r1, r2) for which 0 < r1 ≤ r2 ≤ N.
    // We can verify that L(10) = 30 and L(100) = 3442.
    //
    // Find L(100 000).
    const nombre rayon_max = 100000;
    const nombre limite = 2 * arithmetiques::racine_carre(rayon_max);

    std::vector<std::set<nombre>> rayons;
    for (nombre dx = 1; dx < limite; dx += 2)
        for (nombre dy = 1; dy <= dx; dy += 2) {
            if (arithmetiques::PGCD(dx, dy) != 1)
                continue;

            std::set<nombre> R;

            nombre x, y;
            std::tie(x, y) = diophantienne(dx, dy, (dx * dx + dy * dy) / 2);
            while (true) {
                nombre rayon = x * x + y * y;
                if (rayon > rayon_max * rayon_max)
                    break;
                if (lenticular(x, y, dx, dy))
                    R.insert(rayon);

                x += dy;
                y += dx;
            }

            if (!R.empty())
                rayons.push_back(R);
        }

    nombre resultat = 0;
    for (size_t i = 0; i < rayons.size(); ++i) {
        auto &Ri = rayons[i];
        std::set<std::pair<nombre, nombre>> rem;

        for (size_t j = i + 1; j < rayons.size(); ++j) {
            auto &Rj = rayons[j];
            // rem |= {(u, v) for u in Ri & Rj for v in Rj - Ri}
            // Rj -= Ri

            vecteur intersection;
            std::set_intersection(Ri.begin(), Ri.end(), Rj.begin(), Rj.end(), std::back_inserter(intersection));

            vecteur difference;
            std::set_difference(Rj.begin(), Rj.end(), Ri.begin(), Ri.end(), std::back_inserter(difference));

            for (auto u: intersection)
                for (auto v: difference)
                    rem.insert(std::make_pair(u, v));

            for (auto n: Ri)
                Rj.erase(n);
        }

        resultat += Ri.size() * (Ri.size() + 1) / 2 + rem.size();
    }

    return std::to_string(resultat);
}
