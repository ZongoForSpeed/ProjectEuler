#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>

typedef long long nombre;

namespace {
    nombre floor(nombre a, nombre b) {
        return a / b;
    }

    nombre ceil(nombre a, nombre b) {
        return (a + b - 1) / b;
    }

    nombre f(nombre n, nombre x) {
        return floor(x + ceil(n, x), 2);
    }

    long double algorithme(nombre L, nombre R, nombre x) {
        if (f(L, x) == x && f(R, x) == x)
            return 1.0L;
        if (f(L, x) == f(R, x))
            return 1.0L + algorithme(L, R, f(L, x));

        nombre k = ceil(L, x);
        long double resultat = 0;
        nombre somme = 0;

        while (true) {
            nombre k1 = (k - 1) * x + 1, k2 = k * x;
            k1 = std::max(k1, L);
            k2 = std::min(k2, R);
            if (k1 > k2)
                break;
            if (f(k1, x) != x)
                resultat += (k2 - k1 + 1) * algorithme(k1, k2, f(k1, x));
            somme += k2 - k1 + 1;
            ++k;
        }
        resultat = 1.0L + resultat / somme;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(255, "Rounded Square Roots") {
    // We define the rounded-square-root of a positive integer n as the square root of n rounded to the nearest integer.
    //
    // The following procedure (essentially Heron's method adapted to integer arithmetic) finds the rounded-square-root
    // of n:
    // 
    // Let d be the number of digits of the number n.
    // If d is odd, set x0 = 2×10^(d-1)⁄2.
    // If d is even, set x0 = 7×10^(d-2)⁄2.
    // Repeat:
    // 
    //                 xk+1 = floor(xk + ceil(n / xk), 2)
    //                      
    // until xk+1 = xk.
    //
    // As an example, let us find the rounded-square-root of n = 4321.
    // n has 4 digits, so x0 = 7×10(4-2)⁄2 = 70.
    //
    // x1 = floor(70 + ceil(4321 / 70), 2) = 66
    // x2 = floor(66 + ceil(4321 / 66), 2) = 66
    //
    // Since x2 = x1, we stop here.
    // So, after just two iterations, we have found that the rounded-square-root of 4321 is 66 (the actual square root
    // is 65.7343137…).
    //
    // The number of iterations required when using this method is surprisingly low.
    // For example, we can find the rounded-square-root of a 5-digit integer (10,000 ≤ n ≤ 99,999) with an average of
    // 3.2102888889 iterations (the average value was rounded to 10 decimal places).
    //
    // Using the procedure described above, what is the average number of iterations required to find the
    // rounded-square-root of a 14-digit number (10^13 ≤ n < 10^14)?
    // Give your answer rounded to 10 decimal places.
    //
    // Note: The symbols ⌊x⌋ and ⌈x⌉ represent the floor function and ceiling function respectively.
    long double resultat = algorithme(10000000000000LL, 99999999999999LL, 7000000);

    return std::to_string(resultat, 10);
}
