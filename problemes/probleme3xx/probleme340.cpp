#include "../problemes.h"
#include "arithmetique.h"
#include "mpz_nombre.h"

namespace {
    mpz_nombre S(const mpz_nombre& a, const mpz_nombre& b, const mpz_nombre& c) {
        mpz_nombre L = b / a;
        mpz_nombre resultat = b*(b+1)/2 - (b+1)*c + a*(4*a - 3*c)*L*(L+1)/2;
        resultat += (b - L*a + 1) * (4*a - 3*c) * (L+1);
        return resultat;
    }
}

ENREGISTRER_PROBLEME(340, "Crazy Function") {
    // For fixed integers a, b, c, define the crazy function F(n) as follows:
    // F(n) = n - c for all n > b 
    // F(n) = F(a + F(a + F(a + F(a + n)))) for all n ≤ b.
    //
    // Also, define S(a, b, c) = somme n = 0..b F(n)
    //
    // For example, if a = 50, b = 2000 and c = 40, then F(0) = 3240 and F(2000) = 2040.
    // Also, S(50, 2000, 40) = 5204240.
    //
    // Find the last 9 digits of S(21**7, 7**21, 12**7).
    std::cout << "S(50, 2000, 40) = " << S(50, 2000, 40) << std::endl;
    
    mpz_nombre resultat = S(puissance::puissance<size_t>(21, 7u), puissance::puissance<size_t>(7, 21u), puissance::puissance<size_t>(12, 7u));
    resultat %= 1'000'000'000;
    return resultat.to_string();
}
