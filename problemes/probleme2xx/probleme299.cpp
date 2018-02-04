#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "pythagoricien.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(299, "Three similar triangles") {
    // Four points with integer coordinates are selected: A(a, 0), B(b, 0), C(0, c) and D(0, d),
    // with 0 < a < b and 0 < c < d.
    // Point P, also with integer coordinates, is chosen on the line AC so that the three triangles ABP, CDP and BDP are
    // all similar.
    //
    // p299_ThreeSimTri.gif
    // It is easy to prove that the three triangles can be similar, only if a=c.
    //
    // So, given that a=c, we are looking for triplets (a,b,d) such that at least one point P (with integer coordinates)
    // exists on AC, making the three triangles ABP, CDP and BDP all similar.
    //
    // For example, if (a,b,d)=(2,3,4), it can be easily verified that point P(1,1) satisfies the above condition. Note
    // that the triplets (2,3,4) and (2,4,3) are considered as distinct, although point P(1,1) is common for both.
    //
    // If b+d < 100, there are 92 distinct triplets (a,b,d) such that point P exists.
    // If b+d < 100 000, there are 320471 distinct triplets (a,b,d) such that point P exists.
    // If b+d < 100 000 000, how many distinct triplets (a,b,d) are there such that point P exists?
    nombre limite = 100000000;

    nombre resultat = 0;
    Pythagoricien pythagoricien(limite);
    for (auto t: pythagoricien) {
        nombre a, b, c;
        std::tie(a, b, c) = t;

        nombre somme = a + b;
        if (somme < limite) {
            resultat += 2 * (limite / somme);
        }
    }

    for (nombre n = 1; n < limite; n += 2)
        for (nombre m = 1; m < limite; m++) {
            if (arithmetiques::PGCD(m, n) != 1)
                continue;

            nombre g = 2 * n * m;
            nombre a = n * n + 2 * m * m;
            nombre b = g + a;

            if (b > limite / 2)
                break;
            resultat += (limite - 1) / (2 * b);
        }

    return std::to_string(resultat);
}
