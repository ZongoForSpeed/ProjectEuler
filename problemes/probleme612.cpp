#include "premiers.h"
#include "puissance.h"
#include "combinatoire.h"
#include "multidimension.h"

#include "problemes.h"
#include "utilitaires.h"

typedef unsigned long long nombre;

namespace {
    nombre P(nombre n, nombre k) {
        return k > n ? 0 : combinatoire::factorielle(n) / combinatoire::factorielle(n - k);
    }
}

ENREGISTRER_PROBLEME(612, "Friend numbers") {
    // Let's call two numbers friend numbers if their representation in base 10 has at least one common digit.
    // E.g. 1123 and 3981 are friend numbers.
    //
    // Let f(n) be the number of pairs (p,q) with 1≤p<q<n such that p and q are friend numbers.
    // f(100) = 1539.
    //
    // Find f(10**18) mod 1000267129.
    const nombre modulo = 1000267129;
    const nombre modulo2 = 500133565;
    const nombre exposant = 18;
    const nombre limite = puissance::puissance_modulaire<nombre>(10, exposant, modulo);

    multidimension<nombre, 2> T(exposant + 1, 10ul, 0ul);
    multidimension<nombre, 2> U(exposant + 1, 10ul, 0ul);

    T[0][0] = 1;
    for (unsigned n = 1; n <= exposant; ++n) {
        for (unsigned k = 1; k < 10; ++k) {
            T[n][k] = (k * T[n - 1][k] + T[n - 1][k - 1]) % modulo;
            U[n][k - 1] = (k - 1) * T[n][k] % modulo;
        }
    }

    nombre enemies = 0;
    for (nombre n1 = 1; n1 <= exposant; ++n1) {
        for (nombre n2 = 1; n2 <= exposant; ++n2) {
            for (nombre k1 = 1; k1 <= 9; ++k1) {
                for (nombre k2 = 1; k2 <= 9; ++k2) {
                    nombre A = P(9, k1 + k2);
                    enemies += T[n1][k1] * T[n2][k2] % modulo * A % modulo;
                    enemies += T[n1][k1] * U[n2][k2] % modulo * A % modulo;
                    enemies += U[n1][k1] * T[n2][k2] % modulo * A % modulo;
                    enemies %= modulo;
                }
            }
        }
    }

    nombre pairs = (limite - 1 + modulo) * (limite - 2 + modulo) % modulo;

    nombre resultat = (pairs - enemies + modulo) * modulo2 % modulo;
    return std::to_string(resultat);
}
