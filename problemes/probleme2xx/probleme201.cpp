#include "problemes.h"
#include "multidimension.h"

#include <algorithm>
#include <numeric>
#include <execution>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(201, "Subsets with a unique sum") {
    // For any set A of numbers, let sum(A) be the sum of the elements of A.
    // Consider the set B = {1,3,6,8,10,11}.
    // There are 20 subsets of B containing three elements, and their sums are:
    //
    //                                  sum({1,3,6}) = 10,
    //                                  sum({1,3,8}) = 12,
    //                                  sum({1,3,10}) = 14,
    //                                  sum({1,3,11}) = 15,
    //                                  sum({1,6,8}) = 15,
    //                                  sum({1,6,10}) = 17,
    //                                  sum({1,6,11}) = 18,
    //                                  sum({1,8,10}) = 19,
    //                                  sum({1,8,11}) = 20,
    //                                  sum({1,10,11}) = 22,
    //                                  sum({3,6,8}) = 17,
    //                                  sum({3,6,10}) = 19,
    //                                  sum({3,6,11}) = 20,
    //                                  sum({3,8,10}) = 21,
    //                                  sum({3,8,11}) = 22,
    //                                  sum({3,10,11}) = 24,
    //                                  sum({6,8,10}) = 24,
    //                                  sum({6,8,11}) = 25,
    //                                  sum({6,10,11}) = 27,
    //                                  sum({8,10,11}) = 29.
    //
    // Some of these sums occur more than once, others are unique.
    // For a set A, let U(A,k) be the set of unique sums of k-element subsets of A, in our example we find U(B,3) =
    // {10,12,14,18,21,25,27,29} and sum(U(B,3)) = 156.
    //
    // Now consider the 100-element set S = {1², 2², ... , 100²}.
    // S has 100891344545564193334812497256 50-element subsets.
    //
    // Determine the sum of all integers which are the sum of exactly one of the 50-element subsets of S, i.e. find
    // sum(U(S,50)).
    vecteur carres;
    for (nombre n = 1; n < 101; ++n)
        carres.push_back(n * n);

    const nombre K = 50;
    nombre minimum = std::reduce(carres.begin(), carres.begin() + K);
    nombre maximum = std::reduce(carres.begin() + K, carres.end());

    multidimension<nombre, 2> somme(K + 1, maximum + 1, 0UL);
    somme[0][0] = 1;

    for (nombre c: carres) {
        auto tmp = somme;
        tmp[0][0] = 1;
        for (nombre k = 0; k < K; ++k) {
            for (nombre s = 0; s < c; ++s)
                tmp[k + 1][s] = somme[k + 1][s];
            for (nombre s = c; s <= maximum; ++s)
                tmp[k + 1][s] = somme[k][s - c] + somme[k + 1][s];
        }

        std::swap(somme, tmp);
    }

    nombre resultat = 0;
    for (nombre n = minimum; n <= maximum; ++n) {
        if (somme[K][n] == 1)
            resultat += n;
    }

    return std::to_string(resultat);
}
