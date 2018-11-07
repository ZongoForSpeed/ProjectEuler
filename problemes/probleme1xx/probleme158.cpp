#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(158,
                     "Exploring strings for which only one character comes lexicographically after its neighbour to the left") {
    // Taking three different letters from the 26 letters of the alphabet, character strings of length three can be formed.
    // Examples are 'abc', 'hat' and 'zyx'.
    // When we study these three examples we see that for 'abc' two characters come lexicographically
    // after its neighbour to the left.
    // For 'hat' there is exactly one character that comes lexicographically after its neighbour to the left. For 'zyx'
    // there are zero characters that come lexicographically after its neighbour to the left.
    // In all there are 10400 strings of length 3 for which exactly one character comes lexicographically after its
    // neighbour to the left.
    // 
    // We now consider strings of n ≤ 26 different characters from the alphabet.
    // For every n, p(n) is the number of strings of length n for which exactly one character comes lexicographically
    // after its neighbour to the left.
    //
    // What is the maximum value of p(n)?
    nombre resultat = 0;
    nombre deux_puissance = 1;
    nombre C = 1;
    for (nombre n = 1; n < 27; ++n) {
        C *= 26 - n + 1;
        C /= n;
        deux_puissance *= 2;
        // p(n) = (2^n-n-1) * C(26,n)
        nombre p = (deux_puissance - n - 1) * C;
        resultat = std::max(resultat, p);
    }

    return std::to_string(resultat);
}
