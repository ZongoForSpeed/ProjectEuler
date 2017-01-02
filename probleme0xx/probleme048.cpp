#include "problemes.h"
#include "arithmetiques.h"
#include "grand_nombre.h"

#include <list>

ENREGISTRER_PROBLEME(48, "Self powers")
{
    // The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
    //
    // Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    grand_nombre resultat = 0;
    for (size_t n = 1; n <= 1000; ++n)
    {
        resultat += grand_nombre::puissance_modulaire(n, n, 10000000000LL);
        resultat = resultat%10000000000LL; 
    }
    
    return resultat.to_string();
}
