#include "problemes.h"
#include "utilitaires.h"
#include "multidimension.h"
#include "arithmetique.h"
#include "racine.h"

namespace {
    bool test(const multidimension<size_t, 2> & PGCDs, size_t a, size_t b, size_t c, size_t d) {
        size_t ab = PGCDs[a][b]-1;
        size_t bc = PGCDs[b][c]-1;
        size_t cd = PGCDs[c][d]-1;
        size_t da = PGCDs[d][a]-1;
        size_t i = (a*b + b*c + c*d + d*a - ab - bc - cd - da - 2)/2;
        return racine::carre_parfait(i) ? true : false;
    }
}

ENREGISTRER_PROBLEME(504, "Square on the Inside") {
    // Let ABCD be a quadrilateral whose vertices are lattice points lying on the coordinate axes as follows:
    //
    // A(a, 0), B(0, b), C(−c, 0), D(0, −d), where 1 ≤ a, b, c, d ≤ m and a, b, c, d, m are integers.
    //
    // It can be shown that for m = 4 there are exactly 256 valid ways to construct ABCD. Of these 256 quadrilaterals, 
    // 42 of them strictly contain a square number of lattice points.
    //
    // How many quadrilaterals ABCD strictly contain a square number of lattice points for m = 100?
    size_t m = 100;
    multidimension<size_t, 2> PGCDs(m + 1, m + 1, 0ul);
    for (size_t i = 1; i < m + 1; ++i)
    for (size_t j = i; j < m + 1; ++j) {
        PGCDs[i][j] = PGCDs[j][i] = arithmetique::PGCD(i, j);
    }
    
    size_t resultat = 0;

    for (size_t a = 1; a < m + 1; ++a)
    for (size_t b = a; b < m + 1; ++b)
    for (size_t c = 1; c < m + 1; ++c)
    for (size_t d = c; d < m + 1; ++d) {
        // ABCD
        resultat += test(PGCDs, a, b, c, d);
        // BACD
        if (b != a) resultat += test(PGCDs, b, a, c, d);
        // ABDC
        if (c != d) resultat += test(PGCDs, a, b, d, c);
        // BADC
        if (a != b && c != d) resultat += test(PGCDs, b, a, d, c);
    }

    return std::to_string(resultat);
}
