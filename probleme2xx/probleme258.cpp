#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <numeric>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    vecteur multiplication(const vecteur & x, const vecteur & y, const nombre masque)
    {
        const size_t n = x.size();
        vecteur z(n, 0);
        for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
        {
            if (i + j >= n)
            {
                z[i+j-n] = (z[i+j-n] + x[i] * y[j]) % masque;
                z[i+j-n+1] = (z[i+j-n+1] + x[i] * y[j]) % masque;
            }
            else
            {
                z[i+j] = (z[i+j] + x[i] * y[j]) % masque;
            }
            
        }
        
        return z;
    }
    
    vecteur puissance_(const vecteur & m, nombre a, const nombre masque)
    {
        if (a == 1)
            return m;
        else if (a % 2 == 0)
        {
            auto mm = puissance_(m, a / 2, masque);
            return multiplication(mm, mm, masque);
        }
        else
        {
            return multiplication(m, puissance_(m, a - 1, masque), masque);
        }
    }
}

ENREGISTRER_PROBLEME(258, "A lagged Fibonacci sequence")
{
    // A sequence is defined as:
    //
    // gk = 1, for 0 ≤ k ≤ 1999
    // gk = gk-2000 + gk-1999, for k ≥ 2000.
    // Find gk mod 20092010 for k = 10^18.
    nombre k = 1000000000000000000ULL;
    nombre masque = 20092010;

    vecteur m(2000, 0); m[1] = 1;
    
    vecteur g = puissance_(m, k, masque);
    nombre resultat = std::accumulate(g.begin(), g.end(), 0ULL) % masque;

    return std::to_string(resultat);
}
