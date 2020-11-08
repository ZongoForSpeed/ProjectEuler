#include <maths/racine.h>
#include "problemes.h"
#include "premiers.h"
#include "puissance.h"

typedef unsigned long long nombre;

namespace {
    bool est_premier(const std::set<nombre> &premiers, nombre n) {
        if (n < *(premiers.rbegin()) + 2) {
            return premiers.find(n) != premiers.end();
        }
        return premiers::miller_rabin(n, 25);
    }

    std::optional<std::pair<nombre, nombre>> factorisation_de_Fermat(nombre n, unsigned int iterations) {
        // https://fr.wikipedia.org/wiki/M%C3%A9thode_de_factorisation_de_Fermat

        // Cas trivial: n est pair
        if (n % 2 == 0)
            return std::make_pair(2, n / 2);

        // Si n est un carré parfait
        auto x = racine::racine_carre(n);
        if (x * x == n)
            return std::make_pair(x, x);

        while (iterations-- > 0) {
            x++;
            // Si x² - n est un carré alors n = x² - y² et donc n = (x - y)(x + y)
            if (auto y = racine::carre_parfait(x * x - n))
                return std::make_pair(x - y.value(), x + y.value());
        }

        return std::nullopt;
    }

    // Retourne le plus grand facteur premier de x
    nombre facteur_premier(const std::set<nombre> &premiers, nombre x, nombre minimum = 0) {
        // Si x est premier alors x est le seul facteur premier (et le plus grand aussi :-) )
        if (x == 1 || est_premier(premiers, x))
            return x;

        nombre resultat = 1;
        for (auto p : premiers) {
            // x est premier
            if (p * p > x)
                break;

            // Si p divise x
            bool divisible = false;
            while (x % p == 0) {
                resultat = std::max<nombre>(resultat, p);
                minimum = std::max(resultat, minimum);
                x /= p;

                // on arrête si x est inférieur au minimum
                if (x < minimum)
                    return resultat;

                divisible = true;
            }

            if (divisible) {
                // On arrête si x est premier ou égal à 1
                if (x == 1 || est_premier(premiers, x))
                    break;

                // On essaie la Méthode de factorisation de Fermat
                if (auto fermat = factorisation_de_Fermat(x, 10)) {
                    return std::max(facteur_premier(premiers, fermat->first, minimum),
                                    facteur_premier(premiers, fermat->second, minimum));
                }
            }
        }

        return std::max(x, resultat);
    }

}

ENREGISTRER_PROBLEME(343, "Fractional Sequences") {
    // For any positive integer k, a finite sequence ai of fractions xi/yi is defined by:
    //      a1 = 1/k and
    //      ai = (xi-1+1)/(yi-1-1) reduced to lowest terms for i>1.
    //
    // When ai reaches some integer n, the sequence stops. (That is, when yi=1.)
    // Define f(k) = n.
    // For example, for k = 20:
    //
    // 1/20 → 2/19 → 3/18 = 1/6 → 2/5 → 3/4 → 4/3 → 5/2 → 6/1 = 6
    //
    // So f(20) = 6.
    //
    // Also f(1) = 1, f(2) = 2, f(3) = 1 and Σf(k^3) = 118937 for 1 ≤ k ≤ 100.
    //
    // Find Σf(k^3) for 1 ≤ k ≤ 2×10^6.
    unsigned int limite = 2'000'000;

    std::set<nombre> premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));

    nombre resultat = 0;
    // https://oeis.org/A070777
    for (nombre i = 1; i <= limite; ++i) {
        // i^3+1 = (i+1)(i^2-i+1)
        // facteur_premier(i^3+1) = max(facteur_premier(i+1), facteur_premier(i^2-i+1))
        nombre a = i + 1;
        nombre b = i * i - i + 1;

        auto facteur_b = facteur_premier(premiers, b);

        // Si a < facteur_b, pas la peine de chercher la décomposition de a
        if (a < facteur_b) {
            resultat += facteur_b - 1;
        } else {
            auto facteur_a = facteur_premier(premiers, a, facteur_b);
            resultat += std::max(facteur_a, facteur_b) - 1;
        }
    }

    return std::to_string(resultat);
}
