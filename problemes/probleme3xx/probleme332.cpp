#include "../problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "racine.h"
#include "utilitaires.h"

namespace {
    typedef std::tuple<long, long, long> point;

    bool plan(const point &p1, const point &p2, const point &p3) {
        auto[x1, y1, z1] = p1;
        auto[x2, y2, z2] = p2;
        auto[x3, y3, z3] = p3;
        return x1 * y2 * z3 + y1 * z2 * x3 + z1 * x2 * y3
               - z1 * y2 * x3 - y1 * x2 * z3 - x1 * z2 * y3 != 0;
    }

    long double angle(const long r, const point &p1, const point &p2) {
        auto[x1, y1, z1] = p1;
        auto[x2, y2, z2] = p2;
        const long double m = x1 * x2 + y1 * y2 + z1 * z2;
        return std::acos(m / (1.0L * r * r));
    }

    // long double angle(const paire & p1, const paire & p2) {
    //     long double phi1 = p1.first;
    //     long double phi2 = p2.first;
    //
    //     long double lambda1 = p1.second;
    //     long double lambda2 = p2.second;
    //
    //     return std::acos(std::sin(phi1)*std::sin(phi2) 
    //                     + std::cos(phi1)*std::cos(phi2)*std::cos(lambda2 - lambda1));
    // }

    long double angle_solide(const long double a, const long double b, const long double c) {
        long double s = (a + b + c) / 2;
        long double e = std::tan(s / 2) * std::tan((s - a) / 2) * std::tan((s - b) / 2) * std::tan((s - c) / 2);
        return 4 * std::atan(std::sqrt(e));
    }
}


ENREGISTRER_PROBLEME(332, "Spherical triangles") {
    // A spherical triangle is a figure formed on the surface of a sphere by three great circular arcs intersecting
    // pairwise in three vertices.
    //
    // p332_spherical.jpg
    // Let C(r) be the sphere with the centre (0,0,0) and radius r.
    // Let Z(r) be the set of points on the surface of C(r) with integer coordinates.
    // Let T(r) be the set of spherical triangles with vertices in Z(r). Degenerate spherical triangles, 
    // formed by three points on the same great arc, are not included in T(r).
    // Let A(r) be the area of the smallest spherical triangle in T(r).
    //
    // For example A(14) is 3.294040 rounded to six decimal places.
    //
    // Find p332_sum.gif A(r). Give your answer rounded to six decimal places.
    const long R = 50;
    std::map<long, std::vector<point>> sphere;

    for (long xx = -R; xx <= R; ++xx)
        for (long yy = -R; yy <= R; ++yy)
            for (long zz = -R; zz <= R; ++zz) {
                if (auto r = racine::carre_parfait(xx * xx + yy * yy + zz * zz)) {
                    sphere[r.value()].emplace_back(xx, yy, zz);
                }
            }

    long double resultat = 0;
    for (long r = 1; r <= R; ++r) {
        const auto &points = sphere[r];
        long double optimum = std::numeric_limits<long double>::max();
        for (auto it1 = points.begin(), en = points.end(); it1 != en; ++it1)
            for (auto it2 = it1 + 1; it2 != en; ++it2)
                for (auto it3 = it2 + 1; it3 != en; ++it3) {
                    const auto &i = *it1;
                    const auto &j = *it2;
                    const auto &k = *it3;
                    if (plan(i, j, k)) {
                        long double a = angle(r, i, j);
                        long double b = angle(r, j, k);
                        long double c = angle(r, k, i);
                        long double e = angle_solide(a, b, c);
                        long double aire = r * r * e;
                        optimum = std::min(optimum, aire);
                    }
                }
        // std::cout << r << ' ' << points.size() << ": " << optimum << std::endl;
        resultat += optimum;
    }
    return format::to_fixed(resultat, 6);
}
