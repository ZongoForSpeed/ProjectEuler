#include <numeric>
#include "problemes.h"
#include "arithmetique.h"
#include "racine.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(261, "Stone Game") {
    // Let us call a positive integer k a square-pivot, if there is a pair of integers m > 0 and n ≥ k, such that the
    // sum of the (m+1) consecutive squares up to k equals the sum of the m consecutive squares from (n+1) on:
    //
    //              (k-m)² + ... + k² = (n+1)² + ... + (n+m)².
    //
    // Some small square-pivots are
    //
    // 4: 3² + 4² = 5²
    // 21: 20² + 21² = 29²
    // 24: 21² + 22² + 23² + 24² = 25² + 26² + 27²
    // 110: 108² + 109² + 110² = 133² + 134²
    // 
    // Find the sum of all distinct square-pivots ≤ 10^10.
    const nombre limite = 10000000000ULL;
    const auto limite_crible = racine::racine_carre<nombre>(limite);

    std::vector<bool> crible(limite_crible, true);
    crible[0] = false;
    crible[1] = false;

    std::vector<nombre> facteurs(limite_crible, 1);

    for (size_t i = 2; i < limite_crible; ++i)
        if (crible[i])
            for (size_t j = i; j < limite_crible; j += i) {
                crible[j] = false;
                size_t k = j;
                size_t d = 0;
                while (k % i == 0) {
                    k /= i;
                    ++d;
                }

                facteurs[j] *= puissance::puissance<size_t>(i, (d + 1) / 2);
            }

    std::set<nombre> pivots;
    for (nombre m = 1; 2 * m * (m + 1) <= limite; m++) {
        nombre M = 2 * m + 1;
        nombre maxy = 2 * m * racine::racine_carre<nombre>(m + 1);
        for (nombre y_ = facteurs[m]; y_ <= maxy; y_ += facteurs[m]) {
            nombre y = y_;
            if (auto s = racine::carre_parfait((m + 1) * (y * y / m + 1))) {
                nombre x = *s;
                if (x % 2 == (m + 1) % 2 && y % 2 == m % 2) {
                    while (true) {
                        if (x >= y + 2 * m + 1 && (y + m) / 2 <= limite)
                            pivots.insert((y + m) / 2);

                        std::tie(x, y) = std::make_pair(M * x + (M + 1) * y, (M - 1) * x + M * y);

                        if ((y + m) / 2 > limite)
                            break;
                    }
                }
            }
        }
    }

    nombre resultat = std::reduce(pivots.begin(), pivots.end());
    return std::to_string(resultat);
}
