#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "utilitaires.h"

namespace {
    // long double x(long double t, long double v) {
    //     // x(t) = (1 - t)^3 + 3 * (1 - t)^2 * t + 3 * (1 - t) * t^2 * v;
    //     //      = 1 - 3 t^2 + 2 t^3 + 3 t^2 v - 3 t^3 v
    //     //      = 1 + t^2 (-3 + 2.t + 3.v - 3t.v)
    //     return std::pow(1 - t, 3) + 3 * std::pow(1 - t, 2) * t + 3 * (1 - t) * t * t * v;
    // }

    long double dx(long double t, long double v) {
        return 3 * t * (-2 + 2 * t + 2 * v - 3 * t * v);
    }

    // long double y(long double t, long double v) {
    //     // x(t) = 3.(1 - t)^2.t.v + 3.(1 - t).t^2 + t^3
    //     //      = 3 t^2 - 2 t^3 + 3 t v - 6 t^2 v + 3 t^3 v
    //     return 3 * std::pow(1 - t, 2) * t * v + 3 * (1 - t) * t * t + t * t * t;
    // }

    long double dy(long double t, long double v) {
        return -3 * (1 - t) * (-v + t * (-2 + 3 * v));
    }

    long double aire(long double v) {
        // Integ y * (dx/dt) * dt t = 0..1
        //      = 1/20 (-10 - 12 v + 3 v^2)
        return std::abs((-10.0L - 12.0L * v + 3 * v * v) / 20);
    }

    long double longueur(long double v, long double dt) {
        long double L = 0;
        for (long double t = dt; t <= 1; t += dt) {
            long double h = std::hypot(dy(t, v), dx(t, v));
            L += h * dt;
        }

        return L;
    }

    long double findV(long double precision) {
        long double inf = 0;
        long double sup = 1;
        while (sup - inf > precision) {
            long double v = (sup + inf) / 2;
            long double S = aire(v);
            if (S > M_PI_4l) {
                sup = v;
            } else {
                inf = v;
            }
        }
        return (sup + inf) / 2;
    }

}

ENREGISTRER_PROBLEME(363, "Bézier Curves") {
    // A cubic Bézier curve is defined by four points: P_0, P_1, P_2, and P_3.
    //
    // The curve is constructed as follows:
    // On the segments P_0 P_1, P_1 P_2, and P_2 P_3 the points Q_0, Q_1, and Q_2 are drawn such that
    // \dfrac{P_0 Q_0}{P_0 P_1} = \dfrac{P_1 Q_1}{P_1 P_2} = \dfrac{P_2 Q_2}{P_2 P_3} = t, with t in [0, 1].
    //
    // On the segments Q_0 Q_1 and Q_1 Q_2 the points R_0 and R_1 are drawn such that<br />
    // \dfrac{Q_0 R_0}{Q_0 Q_1} = \dfrac{Q_1 R_1}{Q_1 Q_2} = t for the same value of t.
    //
    // On the segment R_0 R_1 the point B is drawn such that \dfrac{R_0 B}{R_0 R_1} = t for the same value of t.
    //
    // The Bézier curve defined by the points P_0, P_1, P_2, P_3 is the locus of B as Q_0 takes all possible positions
    // on the segment P_0 P_1.<br />
    // (Please note that for all points the value of t is the same.)
    //
    // From the construction it is clear that the Bézier curve will be tangent to the segments P_0 P_1 in P_0 and
    // P_2 P_3 in P_3.
    //
    // A cubic Bézier curve with P_0 = (1, 0), P_1 = (1, v), P_2 = (v, 1), and P_3 = (0, 1) is used to approximate a
    // quarter circle.<br />
    // The value v > 0 is chosen such that the area enclosed by the lines O P_0, OP_3 and the curve is equal to Pi/4
    // (the area of the quarter circle).
    //
    // By how many percent does the length of the curve differ from the length of the quarter circle?<br />
    // That is, if L is the length of the curve, calculate 100 * \dfrac{L - Pi/2}{\frac{\pi}{2}}<br />
    // Give your answer rounded to 10 digits behind the decimal point.
    long double V = findV(std::pow(0.1L, 15));
    std::cout << "V = " << format::to_fixed(V, 12) << std::endl;
    long double L = longueur(V, 0.00000001L);
    std::cout << "L = " << format::to_fixed(L, 12) << std::endl;
    long double error = 100 * (L - M_PI_2l) / M_PI_2l;

    return format::to_fixed(error, 10);
}
