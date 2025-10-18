#include "premiers.h"
#include "problemes.h"

ENREGISTRER_PROBLEME(618, "Numbers with a given prime factor sum") {
    // Consider the numbers 15, 16 and 18:
    // 15=3×5 and 3+5=8.
    // 16=2×2×2×2 and 2+2+2+2=8.
    // 18=2×3×3 and 2+3+3=8.
    // 15, 16 and 18 are the only numbers that have 8 as sum of the prime factors (counted with multiplicity).
    //
    // We define S(k) to be the sum of all numbers n where the sum of the prime factors (with multiplicity) of n is k.
    // Hence S(8)=15+16+18=49.
    // Other examples: S(1)=0, S(2)=2, S(3)=3, S(5)=5+6=11.
    //
    // The Fibonacci sequence is F1=1,F2=1,F3=2,F4=3,F5=5, ....
    // Find the last nine digits of ∑k=2..24 S(Fk).
    const size_t limite = 50000;
    const size_t modulo = 1'000'000'000;

    std::vector<size_t> premiers;
    premiers::crible2<size_t>(limite, std::back_inserter(premiers));

    std::vector<size_t> F(limite, 0);
    F[0] = 1;

    for (auto &p: premiers) {
        for(size_t i = p; i < limite; ++ i) {
            F[i] =  (F[i] + F[i - p] * p) % modulo;
        }
    }

    size_t resultat = 0;
    for (size_t i = 2, a = 1, b = 1; i <= 24; ++i) {
        size_t c = a + b;
        // std::cout << "a = " << a << std::endl;
        resultat += F[a];
        b = a;
        a = c;
    }

    return std::to_string(resultat % modulo);
}
