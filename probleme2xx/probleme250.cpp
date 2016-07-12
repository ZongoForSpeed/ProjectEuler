#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(250, "250250")
{
    // Find the number of non-empty subsets of {1^1, 2^2, 3^3,..., 250250^250250}, 
    // the sum of whose elements is divisible by 250. Enter the rightmost 16 
    // digits as your answer.
    nombre masque = puissance::puissance<nombre>(10, 16);
    
    nombre m = 250;
    vecteur frequence(m, 0);
    for (nombre i = 1; i <= 250250; ++i)
    {
        frequence[puissance::puissance_modulaire<nombre>(i, i, m)] += 1;
    }
    
    vecteur t(m, 0);
    t[0] = 1;
    for (nombre i = 0; i < m; ++i)
    for (nombre j = 0; j < frequence[i]; ++j)
    {
        vecteur _t(m, 0);
        for (nombre k = 0; k < m; ++k)
            _t[k] = (t[k] + t[(m + k - i)%m]) % masque;
        std::swap(t, _t);
    }

    nombre resultat = t.front() - 1;
    std::cout << "Solution: " << resultat << std::endl;
}
