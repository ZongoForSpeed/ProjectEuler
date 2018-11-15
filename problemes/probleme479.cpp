#include "problemes.h"
#include "premiers.h"
#include "arithmetique.h"
#include "arithmetique_modulaire.h"

typedef long long nombre;

ENREGISTRER_PROBLEME(479, "Roots on the Rise") {
    // Let ak, bk, and ck represent the three solutions (real or complex numbers) to the expression 1/x = (k/x)2(k+x2) - kx.
    //
    // For instance, for k = 5, we see that {a5, b5, c5} is approximately {5.727244, -0.363622+2.057397i, -0.363622-2.057397i}.
    //
    // Let S(n) = Σ (ak+bk)^p(bk+ck)^p(ck+ak)^p for all integers p, k such that 1 ≤ p, k ≤ n.
    //
    // Interestingly, S(n) is always an integer. For example, S(4) = 51160.
    //
    //Find S(10**6) modulo 1 000 000 007.
    // (ak+bk)*(bk+ck)*(ck+ak) = 1 - k²
    // Somme (1-k²)^p = ((k^2 - 1) ((1 - k^2)^n - 1))/k^2
    nombre limite = 1'000'000;
    nombre modulo = 1'000'000'007;
    nombre resultat = 0;
    for (nombre k = 1; k <= limite; ++k) {
        // ((k^2 - 1) ((1 - k^2)^n - 1))/k^2
        nombre k2 = puissance::puissance_modulaire<nombre>(k, 2, modulo);
        nombre n = (k2 - 1) * (puissance::puissance_modulaire(1 - k2, limite, modulo) - 1);
        n %= modulo;
        n *= arithmetique_modulaire::inverse_modulaire(k2, modulo);
        n %= modulo;

        resultat += n;
        resultat %= modulo;
    }

    return std::to_string(resultat);
}
