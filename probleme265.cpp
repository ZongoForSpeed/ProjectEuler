#include "problemes.h"
#include "puissance.h"
#include "timer.h"

#include <iostream>
#include <vector>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;

namespace
{
    nombre BinaryCircles(ensemble & S, nombre l, nombre limite)
    {
        if (S.size() == limite)
            return l;
            
        l *= 2;
        
        nombre t = l % limite;
        
        nombre s = 0;
        
        if (S.count(t) == 0)
        {
            S.insert(t);
            s += BinaryCircles(S, l, limite);
            S.erase(t);
        }
        
        ++t;
        if (S.count(t) == 0)
        {
            S.insert(t);
            s += BinaryCircles(S, l + 1, limite);
            S.erase(t);
        }
        
        return s;
    }
}

ENREGISTRER_PROBLEME(265, "Binary Circles")
{
    Timer t("probleme 265");
    // 2N binary digits can be placed in a circle so that all the N-digit clockwise subsequences are distinct.
    //
    // For N=3, two such circular arrangements are possible, ignoring rotations:
    //
    // For the first arrangement, the 3-digit subsequences, in clockwise order, are:
    //                  000, 001, 010, 101, 011, 111, 110 and 100.
    //
    // Each circular arrangement can be encoded as a number by concatenating the binary digits starting with the subsequence of all zeros as the most significant bits and proceeding clockwise. The two arrangements for N=3 are thus represented as 23 and 29:
    // 
    // 00010111 2 = 23
    // 00011101 2 = 29
    // 
    // Calling S(N) the sum of the unique numeric representations, we can see that S(3) = 23 + 29 = 52.
    //
    // Find S(5).
    const nombre N = 5;
    std::set<nombre> S { 0 };
    const nombre resultat = BinaryCircles(S, 0, puissance::puissance<nombre>(2, N)) / puissance::puissance<nombre>(2, N - 1);

    std::cout << "Solution: " << resultat << std::endl;
}
