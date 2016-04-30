#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(76, "Counting summations")
{
    // It is possible to write five as a sum in exactly six different ways:
    //
    //      4 + 1
    //      3 + 2
    //      3 + 1 + 1
    //      2 + 2 + 1
    //      2 + 1 + 1 + 1
    //      1 + 1 + 1 + 1 + 1
    //
    // How many different ways can one hundred be written as a sum of at least two positive integers?
    size_t limite = 100;
    vecteur partition(limite + 1, 0);
    partition[0] = 1;
    for (size_t n = 1; n <= limite; ++n)
    {
        nombre p = 0;
        for (size_t k = 1; k <= n; ++k)
        {
        	if (2*n >= k*(3*k - 1))
        		p += (k%2 == 0 ? (-1) : 1) * partition[n - k*(3*k - 1) / 2];
        	if (2*n >= k*(3*k + 1))
        		p += (k%2 == 0 ? (-1) : 1) * partition[n - k*(3*k + 1) / 2];
        }
        
        partition[n] = p;
    }
    
    std::cout << "Solution: " << partition.back() - 1 << std::endl;
}
