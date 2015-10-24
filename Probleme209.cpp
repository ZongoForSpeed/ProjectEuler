#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"
#include "Graphe.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

namespace
{
    nombre combinaison(nombre n)
    {
        nombre resultat = 0;
        for (nombre k = 0; k < n / 2 + 1; ++k)
        {
            if (k == 0)
                ++resultat;
            else
            {
                resultat += n * combinatoire::coefficient_binomial(n - k - 1, k - 1) / k;
            }
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(209, "Circular Logic")
{
    Timer timer("probleme 209");
    // A k-input binary truth table is a map from k input bits (binary digits, 0 [false] or 1 [true]) 
    // to 1 output bit. For example, the 2-input binary truth tables for the logical AND and XOR 
    // functions are:
    //
    //                  x	y	x AND y         x	y	x XOR y
    //                  0	0	    0           0	0	    0
    //                  0	1	    0           0	1	    1
    //                  1	0	    0           1	0	    1
    //                  1	1	    1           1	1	    0
    // 
    // How many 6-input binary truth tables, τ, satisfy the formula
    //
    // τ(a, b, c, d, e, f) AND τ(b, c, d, e, f, a XOR (b AND c)) = 0
    //
    // for all 6-bit inputs (a, b, c, d, e, f) ?
    nombre limite = 1 << 6;
    Tarjan::graphe G;
    for (nombre i = 0; i < limite; ++i)
    {
        nombre a = i >> 5 & 1;
        nombre b = i >> 4 & 1;
        nombre c = i >> 3 & 1;
        nombre j = (i << 1 & 63) + (a ^ (b & c));
        
        G[i].push_back(j);
        G[j].push_back(i);
    }
    
    Tarjan tarjan(G);
    tarjan.algorithme();
    
    nombre resultat = 1;
    for (auto composante: tarjan.resultat)
    {
        resultat *= combinaison(composante.size());
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
