#include "problemes.h"
#include "chiffres.h"
#include "racine.h"
#include "timer.h"

typedef unsigned long long nombre;

namespace {
    nombre somme_arrangement(const std::deque<nombre> &chiffres, unsigned long long arrangement) {
        nombre somme = 0;
        nombre x = chiffres[0];
        for (size_t n = 0; n < chiffres.size() - 1; ++n) {
            if ((arrangement >> n) & 1) {
                somme += x;
                x = chiffres[n + 1];
            } else {
                x *= 10;
                x += chiffres[n + 1];
            }
        }
        somme += x;

        return somme;
    }

    bool S(nombre n) {
        auto chiffres = chiffres::extraire_chiffres(n, 10);
        nombre sqrt = racine::racine_carre(n);
        nombre limite = 1ull << (chiffres.size() - 1);
        for (nombre arrangement = 0; arrangement < limite; ++arrangement) {
            nombre somme = somme_arrangement(chiffres, arrangement);
            if (sqrt == somme) {
                return true;
            }
        }

        return false;
    }

    nombre T(nombre limite) {
        nombre somme = 0;
        for (nombre n = 3; n * n <= limite; ++n) {
            if (S(n * n)) {
                std::cout << n << "² = " << n * n << std::endl;
                somme += n * n;
            }
        }

        return somme;
    }
}

ENREGISTRER_PROBLEME(719, "Number Splitting") {
    // We define an S-number to be a natural number, n, that is a perfect square and its square root can be obtained by
    // splitting the decimal representation of n into 2 or more numbers then adding the numbers.
    //
    // For example, 81 is an S-number because √81 = 8 + 1.
    //6724 is an S-number: √6724 = 6 + 72 + 4.
    //8281 is an S-number: √8281 = 8 + 2 + 81 = 82 + 8 + 1.
    //9801 is an S-number: √9801 = 98 + 0 + 1.
    //
    //Further we define T(N) to be the sum of all S-numbers n <= N. You are given T(10^4) = 41333.
    //
    //Find T(10^12)
    std::cout << std::boolalpha << "S(81) = " << S(81) << std::endl;

    std::cout << "S(3025) = " << S(3025) << std::endl;
    std::cout << "S(6724) = " << S(6724) << std::endl;
    std::cout << "S(8281) = " << S(8281) << std::endl;
    std::cout << "S(9801) = " << S(9801) << std::endl;

    std::cout << "T(10'000) = " << T(10'000) << std::endl;

    nombre resultat = T(1'000'000'000'000);
    std::cout << "T(1'000'000'000'000) = " << resultat << std::endl;
    return std::to_string(resultat);
}
