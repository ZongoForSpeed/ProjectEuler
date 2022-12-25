#include "problemes.h"
#include "arithmetique.h"


typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> point;

namespace {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

    struct polygone {
        std::vector<point> points;
        long double aire;
    };

#pragma clang diagnostic pop

    long double aire(const point &A, const point &B, const point &C) {
        nombre determinant = (B.first - A.first) * (C.second - A.second)
                             - (C.first - A.first) * (B.second - A.second);
        return std::abs(determinant) / 2.0L;
    }

    long double determinant(const point &A, const point &B, const point &C) {
        return (B.first - A.first) * (C.second - B.second)
               - (B.second - A.second) * (C.first - B.first);
    }

    bool inclus(const polygone &p, const point &c) {
        const size_t n = p.points.size();
        long double aire_totale = 0.0L;
        for (size_t k = 0; k < n; ++k) {
            aire_totale += aire(c, p.points[k], p.points[(k + 1) % n]);
        }
        return std::abs(aire_totale - p.aire) < 0.000001L;
    }

    bool convexe(const polygone &p) {
        size_t n = p.points.size();
        short signe = 0;
        for (size_t k = 0; k < n; ++k) {
            long double d = determinant(p.points[k], p.points[(k + 1) % n], p.points[(k + 2) % n]);
            if (signe == 0)
                signe = arithmetique::signe(d);
            else if (arithmetique::signe(d) != signe)
                return false;
        }

        return true;
    }

    std::vector<polygone> algorithme(const std::vector<polygone> &polygones,
                                     const std::map<std::pair<point, point>, std::vector<std::pair<point, long double>>> &dictionnaire) {
        std::vector<polygone> resultat;
        for (auto &item: polygones) {
            auto &v1 = item.points.back();
            auto &v2 = item.points.front();
            auto edge = std::make_pair(v2, v1);
            if (auto it = dictionnaire.find(edge);it != dictionnaire.end()) {
                for (auto &[p, aire]: it->second) {
                    if (!inclus(item, p)) {
                        polygone q = item;
                        q.points.push_back(p);
                        q.aire += aire;
                        if (convexe(q))
                            resultat.push_back(q);
                    }
                }
            }
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(252, "Convex Holes") {
    // Given a set of points on a plane, we define a convex hole to be a convex 
    // polygon having as vertices any of the given points and not containing any
    // of the given points in its interior (in addition to the vertices, other 
    // given points may lie on the perimeter of the polygon).
    //
    // As an example, the image below shows a set of twenty points and a few such 
    // convex holes. The convex hole shown as a red heptagon has an area equal 
    // to 1049694.5 square units, which is the highest possible area for a convex
    // hole on the given set of points.
    //
    // For our example, we used the first 20 points (T2k−1, T2k), for k = 1,2,…,20,
    // produced with the pseudo-random number generator:
    //
    //                              S0	    = 	290797 
    //                              Sn+1	= 	Sn² mod 50515093
    //                              Tn  	= 	(Sn mod 2000) − 1000 
    //
    // i.e. (527, 144), (−488, 732), (−454, −947), …
    //
    // What is the maximum area for a convex hole on the set containing the first
    // 500 points in the pseudo-random sequence?
    // 
    // Specify your answer including one digit after the decimal point.
    size_t taille = 500;
    vecteur S{290797};
    for (size_t n = 0; n < 2 * taille; ++n) {
        S.push_back((S.back() * S.back()) % 50515093);
    }
    vecteur T;
    for (nombre s: S) T.push_back(s % 2000 - 1000);

    std::vector<point> points;
    for (size_t k = 1; k < taille + 1; ++k) {
        points.emplace_back(T[2 * k - 1], T[2 * k]);
    }

    std::vector<polygone> triangles;

    for (auto it1 = points.begin(), en = points.end(); it1 != en; ++it1)
        for (auto it2 = it1 + 1; it2 != en; ++it2)
            for (auto it3 = it2 + 1; it3 != en; ++it3) {
                const point &A = *it1;
                const point &B = *it2;
                const point &C = *it3;

                const long double ABC = aire(A, B, C);

                bool minimal = true;
                for (const point &D: points)
                    if (A != D && B != D && C != D) {
                        if (std::abs(aire(A, B, D) + aire(A, D, C) + aire(D, B, C) - ABC) < 0.000001L) {
                            minimal = false;
                            break;
                        }
                    }

                if (minimal) {
                    polygone t{{A, B, C}, ABC};
                    triangles.push_back(std::move(t));
                }
            }

    std::map<std::pair<point, point>, std::vector<std::pair<point, long double>>> dictionnaire;
    for (const auto &t: triangles) {
        dictionnaire[std::make_pair(t.points[0], t.points[1])].emplace_back(t.points[2], t.aire);
        dictionnaire[std::make_pair(t.points[1], t.points[2])].emplace_back(t.points[0], t.aire);
        dictionnaire[std::make_pair(t.points[2], t.points[0])].emplace_back(t.points[1], t.aire);
        dictionnaire[std::make_pair(t.points[1], t.points[0])].emplace_back(t.points[2], t.aire);
        dictionnaire[std::make_pair(t.points[2], t.points[1])].emplace_back(t.points[0], t.aire);
        dictionnaire[std::make_pair(t.points[0], t.points[2])].emplace_back(t.points[1], t.aire);
    }

    long double resultat = 0.0L;

    auto polygones = triangles;
    while (!polygones.empty()) {
        auto max = std::max_element(polygones.begin(), polygones.end(),
                                    [](const polygone &p1, const polygone &p2) { return p1.aire < p2.aire; }
        );
        std::cout << max->points << " = " << std::to_fixed(max->aire, 1) << std::endl;
        resultat = std::max(max->aire, resultat);
        polygones = algorithme(polygones, dictionnaire);
    }

    return std::to_fixed(resultat, 1);
}
