#include "../problemes.h"
#include "arithmetique.h"

#include <numeric>

ENREGISTRER_PROBLEME(351, "Hexagonal orchards") {
    // A hexagonal orchard of order n is a triangular lattice made up of points within a regular hexagon with side n.
    // The following is an example of a hexagonal orchard of order 5:
    //
    // p351_hexorchard.png
    //
    // Highlighted in green are the points which are hidden from the center by a point closer to it. It can be seen that
    // for a hexagonal orchard of order 5, 30 points are hidden from the center.
    //
    // Let H(n) be the number of points hidden from the center in a hexagonal orchard of order n.
    //
    // H(5) = 30. H(10) = 138. H(1 000) = 1177848.
    //
    //Find H(100 000 000).
    const size_t n = 100'000'000;

    size_t taille = n + 1;
    std::vector<bool> crible(taille, true);
    std::vector<size_t> phi(taille, 0);

    std::iota(phi.begin(), phi.end(), 0ul);

    size_t resultat = 0;
    for (size_t i = 2; i < taille; ++i) {
        if (crible[i]) {
            for (size_t j = i; j < taille; j += i) {
                crible[j] = false;
                phi[j] /= i;
                phi[j] *= i - 1;
            }
        }
        resultat += i - phi[i];
    }

    return std::to_string(6 * resultat);
}
