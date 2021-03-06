#include "problemes.h"
#include "chiffres.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(52, "Permuted multiples") {
    // It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a
    // different order.
    // 
    // Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
    nombre n = 1;
    nombre resultat = 0;
    while (true) {
        bool trouve = true;
        for (nombre k = 2; trouve && k < 7; ++k) {
            trouve &= chiffres::permutation_chiffres(n, k * n);
        }
        if (trouve) {
            resultat = n;
            break;
        }
        ++n;
    }
    return std::to_string(resultat);
}
