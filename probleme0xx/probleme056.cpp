#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"
#include "mp_nombre.h"

#include <list>

ENREGISTRER_PROBLEME(56, "Powerful digit sum")
{
    // A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost 
    // unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the 
    // digits in each number is only 1.
    //
    // Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
    mp_nombre maximum = 0;
    for (size_t a = 1; a < 100; ++a)
    for (size_t b = 1; b < 100; ++b)
    {
        mp_nombre somme = mp_nombre::puissance(a,b).somme_chiffres();
        maximum = std::max(maximum, somme);
    }
    return maximum.to_string();
}
