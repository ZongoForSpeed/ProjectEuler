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

ENREGISTRER_PROBLEME(76, "Counting summations")
{
    Timer t("probleme 76");
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
    nombre limite = 100;
    vecteur partition(limite + 1, 0);
    partition[0] = 1;
    for (nombre n = 1; n <= limite; ++n)
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
        
        partition[n] = p;
    }
    
    std::cout << "Solution: " << partition.back() - 1 << std::endl;
}
