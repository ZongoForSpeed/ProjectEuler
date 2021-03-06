#include "problemes.h"
#include "chiffres.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(36, "Double-base palindromes") {
    // The decimal number, 585 = 1001001001_2 (binary), is palindromic in both bases.
    //
    // Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
    //
    // (Please note that the palindromic number, in either base, may not include leading zeros.)
    nombre resultat = 0;
    for (nombre n = 1; n < 1000000; ++n) {
        if (chiffres::palindrome(n, 10) && chiffres::palindrome(n, 2))
            resultat += n;
    }
    return std::to_string(resultat);
}
