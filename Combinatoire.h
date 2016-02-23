#pragma once

namespace combinatoire
{
    template<typename Nombre>
    Nombre coefficient_binomial(Nombre n, Nombre p)
    {
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n/2)
            p = n-p;
        Nombre numerateur = 1;
        Nombre denominateur = 1;
        for (Nombre k = 0; k < p; ++k)
        {
            numerateur *= (n - k);
            denominateur *= (k + 1);
        }
        
        return numerateur / denominateur;
    }
    
    template<typename Nombre>
    Nombre factorielle(Nombre n)
    {
        Nombre resultat = 1;
        for (Nombre k = 2; k <= n; ++k) resultat *= k;
        return resultat;
    }
}
