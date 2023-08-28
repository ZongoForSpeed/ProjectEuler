#include "problemes.h"
#include "timer.h"

#include "arithmetique.h"
#include "mpz_nombre.h"

typedef size_t nombre;

namespace {
    nombre d(nombre exposant, nombre x) {
        nombre d = puissance::puissance_modulaire<nombre>(10, exposant - 1, x);
        d *= 10;
        d /= x;
        return d % 10;
    }

    nombre S(nombre base) {
        nombre result = 0;
        for (nombre f = 1; f <= base; ++f) {
            result += d(base, f);
        }
        return result;
    }

}

ENREGISTRER_PROBLEME(820, "Nth Digit of Reciprocals") {
    // Let d_n(x) be the n<sup>th</sup> decimal digit of the fractional part of x, or 0 if the fractional part has fewer than n digits.
    //For example:
    //
    // d_7 ( 1 ) = d_7 ( 1 / 2 ) = d_7 ( 1 / 4 ) = d_7 ( 1 / 5 ) = 0
    // d_7 ( 1 / 3 ) = 3 since 1 / 3 = 0.333333*3*333...
    // d_7 ( 1 / 6 ) = 6 since 1 / 6 = 0.166666*6*666...
    // d_7 ( 1 / 7 ) = 1 since 1 / 7 = 0.142857*1*428...
    //
    // Let S(n) = \sum_{k=1}^n d_n ( 1 / k ).
    // You are given:
    //
    // S(7) = 0 + 0 + 3 + 0 + 0 + 6 + 1 = 10
    // S(100) = 418
    //
    // Find S(10^7).
    std::cout << "d(7, 1) = " << d(7, 1) << std::endl;
    std::cout << "d(7, 2) = " << d(7, 2) << std::endl;
    std::cout << "d(7, 3) = " << d(7, 3) << std::endl;
    std::cout << "d(7, 4) = " << d(7, 4) << std::endl;
    std::cout << "d(7, 5) = " << d(7, 5) << std::endl;
    std::cout << "d(7, 6) = " << d(7, 6) << std::endl;
    std::cout << "d(7, 7) = " << d(7, 7) << std::endl;

    std::cout << "S(7) = " << S(7) << std::endl;
    std::cout << "S(100) = " << S(100) << std::endl;

    return std::to_string(S(10'000'000));
}
