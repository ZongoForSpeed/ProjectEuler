#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(78)
{
    Timer t("probleme 78");
    // Let p(n) represent the number of different ways in which n coins can be separated into piles.
    // For example, five coins can be separated into piles in exactly seven different ways, 
    // so p(5)=7.
    //
    //      OOOOO
    //      OOOO O
    //      OOO OO
    //      OOO O O
    //      OO OO O
    //      OO O O O
    //      O O O O O
    //
    // Find the least value of n for which p(n) is divisible by one million.
    std::vector<nombre> partition = { 1 };
    nombre n = 1;
    while (true)
    {
        nombre p = 0;
        for (nombre k = 1; k <= n; ++k)
        {
            nombre k1 = n - k*(3*k - 1) / 2;
            nombre k2 = n - k*(3*k + 1) / 2;
            if (k1 >= 0)
                p += (k%2 == 0 ? (-1) : 1) * partition[k1];
            if (k2 >= 0)
                p += (k%2 == 0 ? (-1) : 1) * partition[k2];
        }
        
        if (p%1000000 == 0)
            break;
        
        ++n;
        partition.push_back(p%1000000);   
    }
    
    std::cout << "Solution: " << n << std::endl;
}