#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre Ackermann(nombre m, nombre n)
    {
        if (m == 0)
            return n + 1;
        else if (n == 0)
            return Ackermann(m - 1, 1);
        else
            return Ackermann(m - 1, Ackermann(m, n - 1));    
    }

    nombre algorithme(size_t a, nombre m, const vecteur & premiers)
    {
        // calcule 2↑↑a mod m
        if (m < 2)
            return 0;
        
        if (a == 1)
            return 2%m;
        
        std::map<nombre, size_t> d;
        arithmetiques::decomposition(m, premiers, d);
        
        if (d.size() == 1)
        {
            auto facteur = *d.begin();
            if (facteur.first == 2)
            {
                size_t e = facteur.second;
                static const std::vector<nombre> f {0, 2, 4, 16, 65536};
                static const std::vector<size_t> log_f { 0, 1, 2, 4, 16, 65536};
                
                if (a < log_f.size() && e > log_f[a])
                    return f[a];
                else
                    return 0;
            }
            else
            {
                // si m premier avec 2
                // alors 2↑↑a mod m = 2**(2↑↑(n-1) mod phi(m)) mod m
                nombre x = algorithme(a - 1, arithmetiques::phi(m, premiers), premiers);
                return puissance::puissance_modulaire<nombre>(2, x, m);
            }
        }
        else
        {
            vecteur modulos;
            vecteur restes;
            for (auto f: d)
            {
                nombre e = puissance::puissance(f.first, f.second);
                nombre x = algorithme(a, e, premiers);
                
                modulos.push_back(e);
                restes.push_back(x);
            }
            
            return arithmetiques::restes_chinois<nombre>(modulos, restes, premiers);
        }
    }
}

ENREGISTRER_PROBLEME(282, "The Ackermann function")
{
    // For non-negative integers m, n, the Ackermann function A(m, n) is defined 
    // as follows:
    //               | n + 1                     if m = 0
    //      A(m,n) = | A(m - 1, 1)               if m > 0 and n = 0
    //               | A(m - 1, A(m, n - 1))     if m > 0 and n > 0
    //
    // For example A(1, 0) = 2, A(2, 2) = 7 and A(3, 4) = 125.
    //
    // Find ∑ A(n, n), n=0..6 and give your answer mod 14**8.
    nombre modulo = puissance::puissance<nombre, unsigned>(14, 8);
    
    vecteur premiers;
    premiers::crible235<nombre>(1000000, std::back_inserter(premiers));

    nombre resultat = 0;

    resultat += Ackermann(0, 0);
    resultat += Ackermann(1, 1);
    resultat += Ackermann(2, 2);
    resultat += Ackermann(3, 3);
    // A(4, 4) = 2↑↑7 - 3
    resultat += algorithme(7, modulo, premiers) - 3; 
    // A(5, 5) = 2↑↑↑8 - 3
    //         = 2↑↑N - 3
    resultat += 2 * (algorithme(100, modulo, premiers) - 3);
    resultat %= modulo;
    
    return std::to_string(resultat);
}
