#include <racine.h>
#include "problemes.h"
#include "arithmetique.h"
#include "multidimension.h"

namespace {
    long S(long limite) {
        long total = 0;
        long facteur_deux = 1;
        while (limite % 2 == 0) {
            limite /= 2;
            facteur_deux *= 2;
        }

        std::set<std::tuple<long, long, long>> points;
        long limite_m = racine::racine_carre(limite);
        for (long m = 0; m <= limite_m; ++m) {
            long limite_n = racine::racine_carre(limite - m * m);
            for (long n = 0; n <= limite_n; ++n) {
                long limite_p = racine::racine_carre(limite - m * m - n * n);
                for (long p = 0; p <= limite_p; ++p) {
                    if (auto dq = racine::carre_parfait(limite - p * p - n * n - m * m)) {
                        long q = dq.value();
                        long a = std::abs(m * m + n * n - p * p - q * q);
                        long b = 2 * (m * q + n * p);
                        long c = 2 * std::abs(n * q - m * p);
                        if (a > b) {
                            std::swap(a, b);
                        }
                        if (a > c) {
                            std::swap(a, c);
                        }
                        if (b > c) {
                            std::swap(b, c);
                        }

                        if (auto it = points.emplace(a, b, c); it.second) {
                            long compteur = 1;
                            if (a == b || b == c || a == c) {
                                if (a != b || b != c || a != c) {
                                    compteur *= 3;
                                }
                            } else {
                                compteur *= 6;
                            }
                            if (a != 0) {
                                compteur *= 2;
                            }

                            if (b != 0) {
                                compteur *= 2;
                            }

                            if (c != 0) {
                                compteur *= 2;
                            }

                            long manhattan_distance = std::abs(a) + std::abs(b) + std::abs(c);

                            total += manhattan_distance * compteur;
                        }
                    }
                }
            }
        }

        total *= facteur_deux;
        std::cout << "S(" << limite * facteur_deux << ") = " << total << std::endl;
        return total;
    }
}

ENREGISTRER_PROBLEME(360, "Scary Sphere") {
    // Given two points (x1,y1,z1) and (x2,y2,z2) in three dimensional space, the Manhattan distance between those
    // points is defined as |x1-x2|+|y1-y2|+|z1-z2|.
    //
    // Let C(r) be a sphere with radius r and center in the origin O(0,0,0).
    // Let I(r) be the set of all points with integer coordinates on the surface of C(r).
    // Let S(r) be the sum of the Manhattan distances of all elements of I(r) to the origin O.
    //
    // E.g. S(45)=34518.
    //
    // Find S(10^10).
    long limite = 10'000'000'000;
    return std::to_string(S(limite));
}
