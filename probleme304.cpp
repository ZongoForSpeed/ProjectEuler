#include "problemes.h"
#include "arithmetiques.h"
#include "grand_nombre.h"

typedef std::vector<grand_nombre> vecteur;

namespace
{
    std::pair<grand_nombre, grand_nombre> fibonacci_(grand_nombre n, grand_nombre modulo)
    {
        if (n == 0)
            return std::make_pair(1,0);
        
        static std::map<grand_nombre, std::pair<grand_nombre, grand_nombre>> cache;
        auto it = cache.find(n);
        if (it != cache.end())
            return it->second;
        
        std::pair<grand_nombre, grand_nombre> p = fibonacci_(n/2, modulo);
        grand_nombre fk = p.second;
        grand_nombre fk_1 = p.first;
        
        std::pair<grand_nombre, grand_nombre> resultat;
        
        if (n%2 == 0)
            resultat = std::make_pair(fk * fk + fk_1 * fk_1, fk * (2 * fk_1 + fk));
        else
            resultat = std::make_pair(fk * (2 * fk_1 + fk), (fk_1 + fk)*(fk_1 + fk) + fk * fk);
        
        resultat.first %= modulo;
        resultat.second %= modulo;
        
        cache[n] = resultat;
        return resultat;
    }
    
    grand_nombre fibonacci(grand_nombre n, grand_nombre modulo)
    {
        return fibonacci_(n, modulo).second;
    }
}

ENREGISTRER_PROBLEME(304, "Primonacci")
{
    // For any positive integer n the function next_prime(n) returns the smallest
    // prime p such that p>n.
    //
    // The sequence a(n) is defined by:
    // a(1)=next_prime(10**14) and a(n)=next_prime(a(n-1)) for n>1.
    //
    // The fibonacci sequence f(n) is defined by: f(0)=0, f(1)=1 and 
    // f(n)=f(n-1)+f(n-2) for n>1.
    //
    // The sequence b(n) is defined as f(a(n)).
    //
    // Find ∑b(n) for 1≤n≤100 000. Give your answer mod 1234567891011.
    const grand_nombre modulo = 1234567891011ULL;
    const grand_nombre a0 = grand_nombre::puissance(10, 14);
    vecteur a(100000 + 1, a0);
    grand_nombre resultat = 0;
    for (size_t n = 1; n < a.size(); ++n)
    {
        a[n] = a[n - 1].premier_suivant();
        resultat += fibonacci(a[n], modulo);
    }

    resultat %= modulo;

    return resultat.to_string();
}
