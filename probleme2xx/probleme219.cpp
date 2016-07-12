#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <queue>

// #include <boost/multiprecision/gmp.hpp>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(219, "Skew-cost coding")
{
    // Let A and B be bit strings (sequences of 0's and 1's).
    // If A is equal to the leftmost length(A) bits of B, then A is said to be a prefix of B.
    // For example, 00110 is a prefix of 001101001, but not of 00111 or 100110.
    //
    // A prefix-free code of size n is a collection of n distinct bit strings such that no string is
    // a prefix of any other. For example, this is a prefix-free code of size 6:
    //
    // 0000, 0001, 001, 01, 10, 11
    //
    // Now suppose that it costs one penny to transmit a '0' bit, but four pence to transmit a '1'.
    // Then the total cost of the prefix-free code shown above is 35 pence, which happens to be the 
    // cheapest possible for the skewed pricing scheme in question.
    // In short, we write Cost(6) = 35.
    //
    // What is Cost(10^9) ?
    nombre limite = 1000000000ULL;
    
    vecteur S {1, 0, 0, 0, limite - 1};
    nombre a = 0;
    while (S.back() > 0)
    {
        S = { S.front() + S[1], S[2], S[3], S.front(), S.back() - S.front() };
        a += 1;
    }
    
    nombre resultat = 0;
    for (size_t n = 0; n < S.size(); ++n)
    {
        resultat += (a + static_cast<nombre>(n))*S[n];
    }

    std::cout << "Solution: " << resultat << std::endl;
}
