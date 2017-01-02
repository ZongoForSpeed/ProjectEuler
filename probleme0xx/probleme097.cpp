#include "problemes.h"
#include "arithmetiques.h"
#include "grand_nombre.h"

ENREGISTRER_PROBLEME(97, "Large non-Mersenne prime")
{
    // The first known prime found to exceed one million digits was discovered in 1999, and is a 
    // Mersenne prime of the form 2^6972593−1; it contains exactly 2,098,960 digits. Subsequently
    // other Mersenne primes, of the form 2p−1, have been found which contain more digits.
    //
    // However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 
    // digits: 28433×2^7830457+1.
    // 
    // Find the last ten digits of this prime number.
    grand_nombre masque = grand_nombre::puissance(10, 10);
    grand_nombre mersenne = grand_nombre::puissance_modulaire(2, 7830457, masque);
    mersenne = (mersenne * 28433 + 1)%masque;
    return mersenne.to_string();
}
