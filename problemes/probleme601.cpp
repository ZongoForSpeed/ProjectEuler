#include <maths/premiers.h>
#include <maths/arithmetiques.h>
#include "problemes.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre PPCM(nombre a, nombre b) {
        nombre m = 1;
        for (nombre n = a; n < b; ++n) {
            m = arithmetiques::PPCM(n, m);
        }

        return m;
    }

    nombre P(nombre s, nombre N) {
        if (s == 1) {
            return (N - 1) / 2;
        }

        nombre x0 = PPCM(2, s + 1);
        nombre x1 = PPCM(2, s + 2);
        return (N - 2) / x0 - (N - 2) / x1;
    }
}

ENREGISTRER_PROBLEME(601, "Divisibility streaks") {
    // For every positive number n we define the function streak(n)=k as the smallest positive integer k such that n+k
    // is not divisible by k+1.
    // E.g:
    // 13 is divisible by 1
    // 14 is divisible by 2
    // 15 is divisible by 3
    // 16 is divisible by 4
    // 17 is NOT divisible by 5
    // So streak(13)=4.
    // Similarly:
    // 120 is divisible by 1
    // 121 is NOT divisible by 2
    // So streak(120)=1.
    //
    // Define P(s,N) to be the number of integers n, 1<n<N, for which streak(n)=s.
    // So P(3,14) = 1 and P(6,10**6) = 14286.
    //
    // Find the sum, as i ranges from 1 to 31, of P(i,4**i).
    std::cout << "P(3, 14) = " << P(3, 14) << std::endl;
    std::cout << "P(6, 1'000'000) = " << P(6, 1'000'000) << std::endl;

    size_t resultat = 0;
    for (nombre i = 1; i < 32; ++i) {
        resultat += P(i, puissance::puissance<nombre>(4, i));
    }
    return std::to_string(resultat);
}
