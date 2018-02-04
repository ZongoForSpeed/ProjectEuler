#include "problemes.h"
#include "arithmetiques.h"

typedef long long nombre;
typedef std::pair<nombre, nombre> point;

ENREGISTRER_PROBLEME(210, "Obtuse Angled Triangles") {
    // Consider the set S(r) of points (x,y) with integer coordinates satisfying |x| + |y| ≤ r.
    // 
    // Let O be the point (0,0) and C the point (r/4,r/4). 
    // Let N(r) be the number of points B in S(r), so that the triangle OBC has an obtuse angle, i.e. the largest angle
    // α satisfies 90°<α<180°.
    // 
    // So, for example, N(4)=24 and N(8)=100.
    // What is N(1,000,000,000)?
    nombre r = 1000000000LL;

    nombre k = r / 4;
    nombre RR = k * k / 2;
    auto R = static_cast<nombre>(sqrtl(RR));

    nombre compteur = 0;
    for (nombre x = k / 2, y = k / 2; x; --x) {
        nombre xx = x * x;
        nombre yy = (y + 1) * (y + 1);
        if (xx + yy < RR) {
            y++;
        }
        compteur += y - x;
    }

    nombre resultat = 24 * k * k + 8 * compteur + 4 * R + (k - 2);
    return std::to_string(resultat);
}
