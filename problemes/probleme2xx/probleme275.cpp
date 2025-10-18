#include "problemes.h"
#include "arithmetique.h"

#include <set>
#include <vector>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    typedef std::pair<nombre, nombre> Point;
    typedef std::set<Point> Points;

    bool symetrique(const Points &P) {
        for (const auto &[x, y]: P) {
            if (P.find(std::make_pair(-x, y)) == P.end())
                return false;
        }

        return true;
    }

    nombre somme_x(const Points &P) {
        nombre resultat = 0;
        for (const auto &[x, y]: P) {
            resultat += x;
        }

        return resultat;
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"

    nombre algorithme(nombre n, Points &P, Points &F, Points &R, nombre x, nombre minimum_x, nombre maximum_x) {
        nombre min_change = n * (2 * minimum_x - n - 1) / 2;
        nombre max_change = n * (2 * maximum_x + n + 1) / 2;

        if (x + min_change > 0 || x + max_change < 0)
            return 0;

        if (n == 0) {
            if (somme_x(P) != 0)
                return 0;
            if (symetrique(P))
                return 2;

            return 1;
        }

        if (F.empty())
            return 0;

        Point f0 = *F.begin();
        F.erase(F.begin());
        R.insert(f0);
        nombre resultat = algorithme(n, P, F, R, x, minimum_x, maximum_x);
        R.erase(f0);
        F.insert(f0);

        if (P.find(f0) != P.end())
            return resultat;

        P.insert(f0);
        F.erase(f0);

        static const std::vector<Point> dp{
                std::make_pair(-1, 0),
                std::make_pair(1, 0),
                std::make_pair(0, -1),
                std::make_pair(0, 1)
        };

        std::vector<Point> NEW;
        for (const auto &[dx, dy]: dp) {
            Point const next(f0.first + dx, f0.second + dy);
            if (next.second <= 0 || F.find(next) != F.end()
                || R.find(next) != R.end() || P.find(next) != P.end())
                continue;

            NEW.push_back(next);
            F.insert(next);
        }

        x += f0.first;
        minimum_x = std::min(minimum_x, f0.first);
        maximum_x = std::max(maximum_x, f0.first);

        resultat += algorithme(n - 1, P, F, R, x, minimum_x, maximum_x);
        P.erase(f0);
        for (const Point &p: NEW)
            F.erase(p);
        F.insert(f0);
        return resultat;
    }

#pragma clang diagnostic pop
}

ENREGISTRER_PROBLEME(275, "Balanced Sculptures") {
    // Let us define a balanced sculpture of order n as follows:
    //
    //    . A polyomino made up of n+1 tiles known as the blocks (n tiles) and the plinth (remaining tile);
    //    . the plinth has its centre at position (x = 0, y = 0);
    //    . the blocks have y-coordinates greater than zero (so the plinth is the unique lowest tile);
    //    . the centre of mass of all the blocks, combined, has x-coordinate equal to zero.
    //
    // When counting the sculptures, any arrangements which are simply reflections about the y-axis, are not counted as
    // distinct. For example, the 18 balanced sculptures of order 6 are shown below; note that each pair of mirror
    // images (about the y-axis) is counted as one sculpture:
    //
    // p275_sculptures2.gif
    //
    // There are 964 balanced sculptures of order 10 and 360505 of order 15.
    // How many balanced sculptures are there of order 18?
    const nombre n = 18;

    Points P{std::make_pair(0, 0)};
    Points F{std::make_pair(0, 1)};
    Points R;
    nombre resultat = algorithme(n, P, F, R, 0, 0, 0) / 2;
    return std::to_string(resultat);
}
