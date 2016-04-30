#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

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
    nombre masque = puissance::puissance<nombre>(10, 10);
    nombre mersenne = puissance::puissance_modulaire<nombre>(2, 7830457, masque);
    mersenne = (mersenne * 28433 + 1)%masque;
    std::cout << "Solution: " << mersenne << std::endl;
}
