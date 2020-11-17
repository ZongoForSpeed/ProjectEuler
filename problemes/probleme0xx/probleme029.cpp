#include "problemes.h"
#include "arithmetique.h"
#include "mpz_nombre.h"

ENREGISTRER_PROBLEME(29, "Distinct powers") {
    // Consider all integer combinations of ab for 2 ≤ a ≤ 5 and 2 ≤ b ≤ 5:
    //
    // 2^2=4, 2^3=8, 2^4=16, 2^5=32
    // 3^2=9, 3^3=27, 3^4=81, 3^5=243
    // 4^2=16, 4^3=64, 4^4=256, 4^5=1024
    // 5^2=25, 5^3=125, 5^4=625, 5^5=3125
    // If they are then placed in numerical order, with any repeats removed, we get the following 
    // sequence of 15 distinct terms:
    //
    // 4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125
    // 
    // How many distinct terms are in the sequence generated by ab for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?
    std::set<mpz_nombre> resultat;
    for (unsigned long a = 2; a <= 100; ++a) {
        for (unsigned long b = 2; b <= 100; ++b) {
            resultat.emplace(mpz_nombre::puissance(a, b));
        }
    }

    return std::to_string(resultat.size());
}
