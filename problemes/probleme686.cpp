#include "problemes.h"
#include "chiffres.h"
#include "timer.h"

namespace {
    size_t p(size_t total, double min, double max) {
        size_t compteur = 0;
        size_t exposant = 0;
        double produit = 1;

        while (compteur < total) {
            produit *= 2;
            if (produit >= 10)
                produit *= 0.1;
            if (produit >= min && produit < max)
                compteur++;
            exposant++;
        }

        return exposant;
    }
}

ENREGISTRER_PROBLEME(686, "Powers of Two") {
    // 2^7 = 128 is the first power of two whose leading digits are "12".
    // The next power of two whose leading digits are "12" is 2^80.
    //
    // Define p(L, n) to be the nth-smallest value of j such that the base 10 representation of 2^j begins with the
    // digits of L.
    // So p(12, 1) = 7 and p(12, 2) = 80.
    //
    // You are also given that p(123, 45) = 12710.
    //
    // Find p(123, 678910).
    std::cout << "p(12, 1) = " << p(1, 1.2, 1.3) << std::endl;
    std::cout << "p(12, 2) = " << p(2, 1.2, 1.3) << std::endl;
    std::cout << "p(123, 45) = " << p(45, 1.23, 1.24) << std::endl;

    return std::to_string(p(678910, 1.23, 1.24));
}
