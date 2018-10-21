#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre G0(size_t n) {
        return combinatoire::catalan<nombre>(n - 2);
    }

    int signe(size_t n) {
        return (n % 2 == 0) ? 1 : -1;
    }

    nombre G1(size_t n, size_t k1) {
        nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * combinatoire::coefficient_binomial<nombre>(k1 - j, j) * G0(n - j);
        }

        return somme;
    }

    nombre G2(size_t n, size_t k1, size_t k2) {
        nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * combinatoire::coefficient_binomial<nombre>(k1 - j, j) * G1(n - j, k2);
        }

        return somme;
    }

    nombre G3(size_t n, size_t k1, size_t k2, size_t k3) {
        nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * combinatoire::coefficient_binomial<nombre>(k1 - j, j) * G2(n - j, k2, k3);
        }

        return somme;
    }

    nombre G4(size_t n, size_t k1, size_t k2, size_t k3, size_t k4) {
        nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * combinatoire::coefficient_binomial<nombre>(k1 - j, j) * G3(n - j, k2, k3, k4);
        }

        return somme;
    }

    nombre C(size_t n) {
        return G4(4 * n, n, n, n, n);
    }
}

ENREGISTRER_PROBLEME(270, "Cutting Squares") {
    // A square piece of paper with integer dimensions N×N is placed with a corner at the origin and two of its sides
    // along the x- and y-axes. Then, we cut it up respecting the following rules:
    //
    //  . We only make straight cuts between two points lying on different sides of the square, and having integer
    //    coordinates.
    //  . Two cuts cannot cross, but several cuts can meet at the same border point.
    //  . Proceed until no more legal cuts can be made.
    // 
    // Counting any reflections or rotations as distinct, we call C(N) the number of ways to cut an N×N square. For
    // example, C(1) = 2 and C(2) = 30 (shown below).
    //
    //                          p270_CutSquare.gif
    // 
    // What is C(30) mod 10**8 ?
    nombre resultat = C(30) % 100000000;
    return resultat.str();
}
