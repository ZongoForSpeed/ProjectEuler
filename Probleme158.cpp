#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <map>
#include <set>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble; 

void probleme158()
{
    Timer timer("probleme 158");
    // Taking three different letters from the 26 letters of the alphabet, character strings of 
    // length three can be formed.
    // Examples are 'abc', 'hat' and 'zyx'.
    // When we study these three examples we see that for 'abc' two characters come lexicographically
    // after its neighbour to the left.
    // For 'hat' there is exactly one character that comes lexicographically after its neighbour to the
    // left. For 'zyx' there are zero characters that come lexicographically after its neighbour to the
    // left.
    // In all there are 10400 strings of length 3 for which exactly one character comes lexicographically
    // after its neighbour to the left.
    // 
    // We now consider strings of n ≤ 26 different characters from the alphabet.
    // For every n, p(n) is the number of strings of length n for which exactly one character comes 
    // lexicographically after its neighbour to the left.
    //
    // What is the maximum value of p(n)?
    nombre resultat = 0;
    nombre deux_puissance = 1;
    nombre C = 1;
    for (nombre n = 1; n < 27; ++n)
    {
        C *= 26 - n + 1;
        C /= n;
        deux_puissance *= 2;
        // p(n) = (2^n-n-1) * C(26,n)
        nombre p = (deux_puissance - n - 1) * C;
        resultat = std::max(resultat, p);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
