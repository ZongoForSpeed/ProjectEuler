#include "problemes.h"
#include "arithmetique.h"

typedef long long nombre;

ENREGISTRER_PROBLEME(40, "Champernowne's constant") {
    // An irrational decimal fraction is created by concatenating the positive integers:
    //
    //                  0.123456789101112131415161718192021...
    //
    // It can be seen that the 12th digit of the fractional part is 1.
    //
    // If dn represents the nth digit of the fractional part, find the value of the following expression.
    //
    //                      d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
    std::stringstream ss;
    for (nombre n = 0; n < 1000000; ++n)
        ss << n;

    const std::string s = ss.str();
    nombre resultat = 1;
    for (size_t p = 0; p < 7; ++p)
        resultat *= s[puissance::puissance(10UL, p)] - '0';
    return std::to_string(resultat);
}
