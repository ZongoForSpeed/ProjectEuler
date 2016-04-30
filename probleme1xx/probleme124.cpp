#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(124, "Ordered radicals")
{
    // The radical of n, rad(n), is the product of the distinct prime factors of n. For example, 
    // 504 = 2^3 × 3^2 × 7, so rad(504) = 2 × 3 × 7 = 42.
    //
    // If we calculate rad(n) for 1 ≤ n ≤ 10, then sort them on rad(n), and sorting on n if the 
    //  radical values are equal, we get:
    //
    //                  Unsorted            Sorted
    //                  n   rad(n)          n   rad(n)  k
    //                  1   1               1   1       1
    //                  2   2	            2   2       2
    //                  3   3               4   2       3
    //                  4   2               8   2       4
    //                  5   5               3   3       5
    //                  6   6               9   3       6
    //                  7   7               5   5       7
    //                  8   2               6   6       8
    //                  9   3               7   7       9
    //                  10  10              10  10      10
    //
    // Let E(k) be the kth element in the sorted n column; for example, E(4) = 8 and E(6) = 9.
    //
    // If rad(n) is sorted for 1 ≤ n ≤ 100000, find E(10000).
    nombre limite = 100000;
    vecteur premiers;
    premiers::crible23<nombre>(limite, std::back_inserter(premiers));
    
    std::vector<paire> rad { paire(0, 0), paire(1, 1) };
    for (nombre n = 2; n < limite + 1; ++n)
    {
        rad.push_back(paire(arithmetiques::radical(n, premiers), n));
    }
    
    std::sort(rad.begin(), rad.end());
    
    nombre resultat = rad.at(10000).second;
    std::cout << "Solution: " << resultat << std::endl;
}
