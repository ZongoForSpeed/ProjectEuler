#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre nombre_triangles(nombre p) {
        // http://mathworld.wolfram.com/IntegerTriangle.html
        if (p % 2 == 1)
            return arithmetiques::arrondi<nombre>((p + 3) * (p + 3), 48);
        else
            return arithmetiques::arrondi<nombre>(p * p, 48);
    }
}

ENREGISTRER_PROBLEME(276, "Primitive Triangles") {
    // Consider the triangles with integer sides a, b and c with a ≤ b ≤ c.
    //
    // An integer sided triangle (a,b,c) is called primitive if gcd(a,b,c)=1.
    //
    // How many primitive integer sided triangles exist with a perimeter not exceeding 10 000 000?
    nombre taille = 10000000;
    nombre resultat = 0;

    vecteur dp(taille + 1, 0);

    for (nombre i = 3; i < taille + 1; ++i) {
        nombre u = nombre_triangles(i) - dp[i];
        resultat += u;
        for (nombre j = 2 * i; j < taille + 1; j += i)
            dp[j] += u;
    }

    return std::to_string(resultat);
}
