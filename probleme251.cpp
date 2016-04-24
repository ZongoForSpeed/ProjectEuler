#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "utilitaires.h"
#include "combinatoire.h"
#include "polygonal.h"

#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(251, "Cardano Triplets")
{
    // A triplet of positive integers (a,b,c) is called a Cardano Triplet if it 
    // satisfies the condition:
    //
    //          cqrt(a + b.sqrt(c)) + cqrt(a - b.sqrt(c)) = 1
    //
    // For example, (2,1,5) is a Cardano Triplet.
    //
    // There exist 149 Cardano Triplets for which a+b+c ≤ 1000.
    //
    // Find how many Cardano Triplets exist such that a+b+c ≤ 110,000,000.
    const nombre u = 110000000;

    nombre resultat = 0;
    for (nombre n = 1, n_max = racine_carre(u / 5); n <= n_max; n++)
    for (nombre d = 1, d_max = racine_carre(u - 5 * n * n - n); d < d_max; d += 2)
    {
        if (arithmetiques::PGCD(d, n) != 1) 
            continue;
            
        nombre q, l;
        arithmetiques::Bezout(d, 8 * n, q, l); // q = d ^ (-1) (mod 8 * n)
        l = -3 * q * q % (8 * n); l += l < 0 ? 8 * n: 0;
        nombre c = u + 1 - (3 * n + d) * (d * d * l + 3) / (8 * n) - n * n * l;
        if (c > 0)
            resultat += c / (8 * n * n * n + (3 * n + d) * d * d) + 1;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
