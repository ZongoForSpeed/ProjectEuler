#include "problemes.h"
#include "premiers.h"

#include <set>
#include <iterator>

typedef long long nombre;

ENREGISTRER_PROBLEME(27, "Quadratic primes") {
    // Euler discovered the remarkable quadratic formula:
    //
    //                                                n² + n + 41
    //
    // It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. 
    // However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41,
    // 41² + 41 + 41 is clearly divisible by 41.
    // 
    // The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0
    // to 79. The product of the coefficients, −79 and 1601, is −126479.
    //
    // Considering quadratics of the form:
    // 
    // n² + an + b, where |a| < 1000 and |b| < 1000
    // 
    // where |n| is the modulus/absolute value of n
    // e.g. |11| = 11 and |−4| = 4
    // Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of
    // primes for consecutive values of n, starting with n = 0.
    std::set<nombre> premiers;
    premiers::crible235<nombre>(1000000, std::inserter(premiers, premiers.begin()));

    auto suite_premier = [&premiers](nombre a, nombre b) -> nombre {
        nombre compteur = 0;
        nombre n = b;

        while (premiers.find(n) != premiers.end()) {
            ++compteur;
            n = compteur * compteur + a * compteur + b;
        }

        return compteur;
    };

    nombre a_max = 0;
    nombre b_max = 0;
    nombre c_max = 0;
    for (nombre b = 2; b < 1000; ++b) {
        if (premiers.find(b) != premiers.end()) {
            for (nombre a = -999; a < 1000; ++a) {
                if (std::llabs(a) > 1) {
                    if (nombre compteur = suite_premier(a, b);compteur > c_max) {
                        c_max = compteur;
                        a_max = a;
                        b_max = b;
                        // std::cout << "(a, b, c) = (" << a << ", " << b << ", " << compteur << ")" << std::endl;
                    }
                }

            }
        }
    }

    return std::to_string(a_max * b_max);
}
