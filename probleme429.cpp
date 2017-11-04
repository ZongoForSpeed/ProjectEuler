#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "chiffres.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(429, "Sum of squares of unitary divisors") {
    // A unitary divisor d of a number n is a divisor of n that has the property gcd(d, n/d) = 1.
    // The unitary divisors of 4! = 24 are 1, 3, 8 and 24.
    // The sum of their squares is 1² + 3² + 8² + 24² = 650.
    //
    // Let S(n) represent the sum of the squares of the unitary divisors of n. Thus S(4!)=650.
    //
    // Find S(100 000 000!) modulo 1 000 000 009.
    size_t limite = 100'000'000;
    nombre modulo = 1'000'000'009;
    
    std::vector<nombre> premiers;
    premiers::crible2<nombre>(limite, std::back_inserter(premiers));
    // http://mathworld.wolfram.com/UnitaryDivisorFunction.html
    // http://oeis.org/A034676
    nombre resultat = 1;
    for (auto p: premiers) {
        nombre compteur = 0;
        for (nombre q = p; q < limite + 1; q *= p) {
            compteur += limite / q;
        }
        
        resultat *= 1 + puissance::puissance_modulaire(p, 2*compteur, modulo);
        resultat %= modulo;
    }
    
    return std::to_string(resultat);
}
