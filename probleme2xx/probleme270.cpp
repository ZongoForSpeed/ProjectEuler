#include "problemes.h"
#include "arithmetiques.h"
#include "mp_nombre.h"

typedef std::vector<mp_nombre> vecteur;

namespace {
    mp_nombre G0(size_t n) {
        return mp_nombre::catalan(n - 2);
    }

    int signe(size_t n) {
        return (n % 2 == 0) ? 1 : -1;
    }

    mp_nombre G1(size_t n, size_t k1) {
        mp_nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * mp_nombre::coefficient_binomial(k1 - j, j) * G0(n - j);
        }

        return somme;
    }

    mp_nombre G2(size_t n, size_t k1, size_t k2) {
        mp_nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * mp_nombre::coefficient_binomial(k1 - j, j) * G1(n - j, k2);
        }

        return somme;
    }

    mp_nombre G3(size_t n, size_t k1, size_t k2, size_t k3) {
        mp_nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * mp_nombre::coefficient_binomial(k1 - j, j) * G2(n - j, k2, k3);
        }

        return somme;
    }

    mp_nombre G4(size_t n, size_t k1, size_t k2, size_t k3, size_t k4) {
        mp_nombre somme = 0;
        for (size_t j = 0; 2 * j < k1 + 1; ++j) {
            somme += signe(j) * mp_nombre::coefficient_binomial(k1 - j, j) * G3(n - j, k2, k3, k4);
        }

        return somme;
    }

    mp_nombre C(size_t n) {
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
    mp_nombre resultat = C(30) % 100000000;
    return resultat.to_string();
}
