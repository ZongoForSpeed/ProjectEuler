#include "problemes.h"
#include "arithmetique.h"
#include "chiffres.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(284, "Steady Squares") {
    // The 3-digit number 376 in the decimal numbering system is an example of numbers with the special property that
    // its square ends with the same digits: 376² = 141376. Let's call a number with this property a steady square.
    //
    // Steady squares can also be observed in other numbering systems. In the base 14 numbering system, the 3-digit
    // number c37 is also a steady square: c37² = aa0c37, and the sum of its digits is c+3+7=18 in the same numbering
    // system. The letters a, b, c and d are used for the 10, 11, 12 and 13 digits respectively, in a manner similar to
    // the hexadecimal numbering system.
    //
    // For 1 ≤ n ≤ 9, the sum of the digits of all the n-digit steady squares in the base 14 numbering system is 2d8
    // (582 decimal). Steady squares with leading 0's are not allowed.
    // 
    // Find the sum of the digits of all the n-digit steady squares in the base 14 numbering system for 1 ≤ n ≤ 10000
    // (decimal) and give your answer in the base 14 system using lower case letters where necessary.
    size_t N = 10000;
    mpz_nombre a = 7;
    mpz_nombre b = 8;

    mpz_nombre answer = a + b + 1;
    mpz_nombre x = a;
    mpz_nombre r = 14;

    for (size_t n = 1; n < N; ++n) {
        mpz_nombre q = r;
        r *= 14;

        size_t d = 0;
        for (; d < 14; ++d) {
            if ((x * x) % r == x) {
                break;
            }
            x += q;
        }
        a = a + d;
        b = b + 13 - d;
        if (d) {
            answer += a;
        }

        if (13 - d) {
            answer += b;
        }
    }

    std::ostringstream oss;
    for (auto c: chiffres::extraire_chiffres(answer.get<size_t>(), 14)) {
        switch (c) {
            case 10:
                oss << 'a';
                break;
            case 11:
                oss << 'b';
                break;
            case 12:
                oss << 'c';
                break;
            case 13:
                oss << 'd';
                break;
            default:
                oss << c;
                break;
        }
    }

    return oss.str();
}
