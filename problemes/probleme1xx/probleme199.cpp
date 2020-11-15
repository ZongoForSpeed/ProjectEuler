#include "problemes.h"
#include "arithmetique.h"

#include <boost/math/constants/constants.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

namespace {
    typedef std::tuple<long double, long double, long double> triplet;

    long double aire(long double k) {
        long double rayon = std::abs(1.0L / k);
        return rayon * rayon * M_PIl;
    }

    long double iteration(std::map<triplet, nombre> &apollonios) {
        long double A = 0.0L;
        std::map<triplet, nombre> resultat;
        for (auto p: apollonios) {
            // k4 = k1 + k2 + k3 +/- 2*sqrt(k1.k2 + k2.k3 + k3.k1)
            auto[k1, k2, k3] = p.first;
            long double k4 = k1 + k2 + k3 + 2.0L * std::sqrt(k1 * k2 + k2 * k3 + k1 * k3);
            A += p.second * aire(k4);
            resultat[std::make_tuple(k4, k1, k2)] += p.second;
            resultat[std::make_tuple(k4, k1, k3)] += p.second;
            resultat[std::make_tuple(k4, k2, k3)] += p.second;
        }

        std::swap(apollonios, resultat);
        return A;
    }
}

ENREGISTRER_PROBLEME(199, "Iterative Circle Packing") {
    // Three circles of equal radius are placed inside a larger circle such that each pair of circles is tangent to one
    // another and the inner circles do not overlap. There are four uncovered "gaps" which are to be filled iteratively
    // with more tangent circles.
    //
    // At each iteration, a maximally sized circle is placed in each gap, which creates more gaps for the next iteration.
    // After 3 iterations (pictured), there are 108 gaps and the fraction of the area which is not covered by circles is
    // 0.06790342, rounded to eight decimal places.
    //
    // What fraction of the area is not covered by circles after 10 iterations?
    // Give your answer rounded to eight decimal places using the format x.xxxxxxxx.
    std::map<triplet, nombre> apollonios;

    // Théorème de Descartes : (k1 + k2 + k3 + k4)² = sqrt(k1² + k2² + k3² + k4²)
    // k4 = k1 + k2 + k3 +/- 2*sqrt(k1.k2 + k2.k3 + k3.k1)
    long double k0 = -1.0L;
    long double k1 = k0 / (3.0L - 2 * std::sqrt(3.0L)); // k1 = k2 = k3

    apollonios[std::make_tuple(k1, k1, k1)] = 1;
    apollonios[std::make_tuple(k1, k1, k0)] = 3;

    long double a0 = aire(k0);
    long double A = 3.0L * aire(k1);

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Iteration 0: " << 1.0L - A / a0 << std::endl;

    for (nombre n = 1; n <= 10; ++n) {
        A += iteration(apollonios);
        std::cout << "Iteration " << n << ": " << 1.0L - A / a0 << std::endl;
    }

    long double resultat = 1.0L - A / a0;
    return std::to_string(resultat, 8);
}
