#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>

typedef unsigned long long nombre;

void probleme036()
{
    Timer t("probleme 36");
    // The decimal number, 585 = 1001001001_2 (binary), is palindromic in both bases.
    //
    // Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
    //
    // (Please note that the palindromic number, in either base, may not include leading zeros.)
    nombre resultat = 0;
    for (nombre n = 1; n < 1000000; ++n)
    {
        if (arithmetiques::palindrome(n, 10) && arithmetiques::palindrome(n, 2))
            resultat += n;
    }
    std::cout << "Solution: " << resultat << std::endl;
}
