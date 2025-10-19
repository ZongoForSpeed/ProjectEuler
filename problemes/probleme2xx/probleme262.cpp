#include "problemes.h"
#include "format.h"
#include "utilitaires.h"

#include <cmath>
#include <optional>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double h(long double x, long double y) {
        return (5000.0L - 0.005L * (x * x + y * y + x * y) + 12.5L * (x + y))
               * std::exp(-std::abs(0.000001L * (x * x + y * y) - 0.0015L * (x + y) + 0.7L));
    }

    long double dh_dx(long double x, long double y) {
        return (h(x + 0.000001L, y) - h(x - 0.000001L, y)) / 0.000002L;
    }

    long double dichotomie(const std::function<long double(long double)> &f, long double x_inf, long double x_sup) {
        while (x_sup - x_inf > 0.0000000001L) {
            long double x_med = (x_sup + x_inf) / 2;
            long double f_med = f(x_med);

            if (f_med < 0) {
                x_sup = x_med;
            } else {
                x_inf = x_med;
            }
        }

        return (x_inf + x_sup) / 2;
    }

    long double
    marche(long double xmin, long double fmin, long double objectif_x, long double objectif_y, long double pas) {
        long double d = 0.0L;
        long double x0 = xmin;
        long double y0 = 0.0L;
        std::optional<long double> t0;
        long double alpha = xmin;

        while (true) {
            alpha += pas;
            long double x = dichotomie([&](long double _x) { return h(_x, alpha - _x) - fmin; }, x0 - 5, x0 + 5);
            long double y = alpha - x;

            long double dy_dx = (y - y0) / (x - x0);
            long double tangente = y + dy_dx * (objectif_x - x) - objectif_y;

            if (t0 && *t0 * tangente < 0 && std::abs(tangente) < 100) {
                return d + std::hypot(x0 - objectif_x, y0 - objectif_y);
            }

            d += std::hypot(x0 - x, y0 - y);
            x0 = x;
            y0 = y;
            t0 = tangente;
        }
    }
}

ENREGISTRER_PROBLEME(262, "Mountain Range") {
    // The following equation represents the continuous topography of a mountainous region, giving the elevation h at
    // any point (x,y):
    //
    //                             p262_formula1.gif
    //
    // A mosquito intends to fly from A(200,200) to B(1400,1400), without leaving the area given by 0 ≤ x, y ≤ 1600.
    //
    // Because of the intervening mountains, it first rises straight up to a point A', having elevation f. Then, while
    // remaining at the same elevation f, it flies around any obstacles until it arrives at a point B' directly above B.
    // 
    // First, determine fmin which is the minimum constant elevation allowing such a trip from A to B, while remaining
    // in the specified area. Then, find the length of the shortest path between A' and B', while flying at that
    // constant elevation fmin.
    //
    // Give that length as your answer, rounded to three decimal places.
    //
    // Note: For convenience, the elevation function shown above is repeated below, in a form suitable for most
    // programming languages:
    // h = ( 5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ) * exp( -abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) )
    long double xmin = dichotomie(
            [](long double x) /*-> long double*/
            {
                return dh_dx(x, 0);
            }, 0.0L, 1600.0L);
    long double fmin = h(xmin, 0.0L);

    long double resultat = marche(xmin, fmin, 200, 200, -1.0L)
                           + marche(xmin, fmin, 1400, 1400, 1.0L);

    return format::to_fixed(resultat, 3);
}
