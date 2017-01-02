#include "problemes.h"
#include "grand_nombre.h"
#include "puissance.h"

ENREGISTRER_PROBLEME(291, "Panaitopol Primes")
{
    // A prime number p is called a Panaitopol prime if (x**4 - y**4)/(x**3 + y**3)
    // for some positive integers x and y.
    //
    // Find how many Panaitopol primes are less than 5×10**15.
    const size_t limite = 5*puissance::puissance<size_t, unsigned>(10, 15);

    size_t resultat = 0;
    for (size_t n = 1; n*n + (n+1)*(n+1) < limite; ++n)
    {
        if (grand_nombre::premier(n*n + (n+1)*(n+1)))
            ++resultat;
    }
    
    return std::to_string(resultat);
}
