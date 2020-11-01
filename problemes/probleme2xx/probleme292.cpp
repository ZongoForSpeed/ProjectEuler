#include "problemes.h"
#include "arithmetique.h"
#include "racine.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    typedef std::tuple<short, short, short> triplet;

    void generer_triplets(const short longueur, std::vector<triplet> &triplets) {
        for (short dx = -longueur; dx <= longueur; ++dx)
            for (short dy = -longueur; dy <= longueur; ++dy) {
                if (auto racine = racine::carre_parfait(dx * dx + dy * dy)) {
                    if (*racine < longueur)
                        triplets.emplace_back(dx, dy, *racine);
                }
            }
    }

    double angle(const triplet &t) {
        return std::atan2(std::get<1>(t), std::get<0>(t));
    }

    bool colineaire(const triplet &a, const triplet &b) {
        return std::get<0>(a) * std::get<1>(b) == std::get<1>(a) * std::get<0>(b);
    }

    size_t suivant(const std::vector<triplet> &triplets, size_t n) {
        size_t i = n + 1;
        while (i < triplets.size() && colineaire(triplets[n], triplets[i])) ++i;
        return i;
    }

    size_t algorithme(const std::vector<triplet> &triplets, short perimetre, short x, short y, short l, size_t i) {
        if (x == 0 && y == 0 && l > 0)
            return 1;

        static std::map<std::tuple<short, short, short, size_t>, size_t> cache;
        auto clef = std::make_tuple(x, y, l, i);
        auto it = cache.find(clef);

        if (it != cache.end())
            return it->second;

        size_t resultat = 0;
        for (size_t k = i; k < triplets.size(); ++k) {
            auto [dx, dy, dl] = triplets[k];
            if (l != dl || x != -dx || y != -dy) {
                short nx = x + dx;
                short ny = y + dy;
                short nl = l + dl;
                short reste = perimetre - nl;

                if (nx * nx + ny * ny <= reste * reste && reste >= 0)
                    resultat += algorithme(triplets, perimetre, nx, ny, nl, suivant(triplets, k));
            }
        }

        cache[clef] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(292, "Pythagorean Polygons") {
    // We shall define a pythagorean polygon to be a convex polygon with the following properties:
    //
    //      - there are at least three vertices,
    //      - no three vertices are aligned,
    //      - each vertex has integer coordinates,
    //      - each edge has integer length.
    //
    // For a given integer n, define P(n) as the number of distinct pythagorean polygons for which the perimeter is ≤ n.
    // Pythagorean polygons should be considered distinct as long as none is a translation of another.
    //
    // You are given that P(4) = 1, P(30) = 3655 and P(60) = 891045.
    // Find P(120).
    short perimetre = 120;

    std::vector<triplet> triplets;
    generer_triplets(perimetre, triplets);
    std::sort(triplets.begin(), triplets.end(),
              [](const triplet &t1, const triplet &t2) {
                  return angle(t1) < angle(t2);
              });

    size_t resultat = algorithme(triplets, perimetre, 0, 0, 0, 0);

    return std::to_string(resultat);
}
