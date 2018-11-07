#include "problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    char lettre(nombre n) {
        static const char *fibo = "ABBAB";
        if (n < 6)
            return fibo[n - 1];
        std::pair<nombre, nombre> ab(1, 1);
        while (ab.second < n) {
            ab = std::make_pair(ab.second, ab.first + ab.second);
        }
        return lettre(n + ab.first - ab.second);
    }
}

ENREGISTRER_PROBLEME(230, "Fibonacci Words") {
    // For any two strings of digits, A and B, we define FA,B to be the sequence (A,B,AB,BAB,ABBAB,...) in which each
    // term is the concatenation of the previous two.
    // 
    // Further, we define DA,B(n) to be the nth digit in the first term of FA,B that contains at least n digits.
    // 
    // Example:
    // 
    // Let A=1415926535, B=8979323846. We wish to find DA,B(35), say.
    // 
    // The first few terms of FA,B are:
    // 1415926535
    // 8979323846
    // 14159265358979323846
    // 897932384614159265358979323846
    // 14159265358979323846897932384614159265358979323846
    // Then DA,B(35) is the 35th digit in the fifth term, which is 9.
    // 
    // Now we use for A the first 100 digits of pi behind the decimal point:
    // 
    // 14159265358979323846264338327950288419716939937510 
    // 58209749445923078164062862089986280348253421170679
    // 
    // and for B the next hundred digits:
    //
    // 82148086513282306647093844609550582231725359408128 
    // 48111745028410270193852110555964462294895493038196 .
    // 
    // Find sum n = 0,1,...,17   10n× DA,B((127+19n)×7n) .
    std::map<char, std::string> F{
            {'A', "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"},
            {'B', "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"}
    };

    nombre resultat = 0;
    for (nombre n = 0; n < 18; ++n) {
        const nombre f = (127 + 19 * n) * puissance::puissance<nombre>(7, n) - 1;
        resultat += static_cast<nombre>(F[lettre(f / 100 + 1)][f % 100] - '0') * puissance::puissance<nombre>(10, n);
    }

    return std::to_string(resultat);
}

