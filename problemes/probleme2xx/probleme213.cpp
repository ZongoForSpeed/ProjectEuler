#include "problemes.h"
#include "arithmetique.h"
#include "matrice.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(213, "Flea Circus") {
    // A 30×30 grid of squares contains 900 fleas, initially one flea per square.
    // When a bell is rung, each flea jumps to an adjacent square at random (usually 4 possibilities, except for fleas
    // on the edge of the grid or at the corners).
    // 
    // What is the expected number of unoccupied squares after 50 rings of the bell? Give your answer rounded to six
    // decimal places.
    nombre taille = 30;

    matrice::matrice<long double> I(taille * taille, taille * taille, 0.0L);
    for (size_t n = 0; n < taille * taille; ++n)
        I(n, n) = 1.0L;

    matrice::matrice<long double> A(taille * taille, taille * taille);
    for (size_t i = 0; i < taille; ++i)
        for (size_t j = 0; j < taille; ++j) {
            nombre ij = i * taille + j;
            vecteur adjacents;
            if (i > 0)
                adjacents.push_back((i - 1) * taille + j);
            if (j > 0)
                adjacents.push_back(i * taille + j - 1);
            if (i < taille - 1)
                adjacents.push_back((i + 1) * taille + j);
            if (j < taille - 1)
                adjacents.push_back(i * taille + j + 1);

            for (auto a: adjacents)
                A(ij, a) = 1.0L / adjacents.size();
        }

    auto An = matrice::puissance_matrice(A, 50);

    long double resultat = 0.0L;
    for (size_t j = 0; j < An.size2(); ++j) {
        long double e = 1.0L;
        for (size_t i = 0; i < An.size1(); ++i)
            e *= 1.0L - An(i, j);
        resultat += e;
    }

    return std::to_string(resultat, 6);
}
