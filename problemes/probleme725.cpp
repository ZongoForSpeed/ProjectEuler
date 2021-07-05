#include "problemes.h"
#include "numerique.h"
#include "premiers.h"
#include "timer.h"
#include "nombre_modulaire.h"
#include "multidimension.h"

namespace {
    size_t S(size_t n, size_t modulo) {
        multidimension<nombre_modulaire, 3> compteur(n + 1, 10ul, 19ul, nombre_modulaire(modulo, 0));
        multidimension<nombre_modulaire, 3> somme(n + 1, 10ul, 19ul, nombre_modulaire(modulo, 0));

        compteur[0][0][0] = 1;
        somme[0][0][0] = 0;
        for (size_t i = 0; i < n; i++) {
            for (size_t mx = 0; mx <= 9; mx++) {
                for (size_t s = 0; s <= 18; s++) {
                    for (size_t d = 0; d <= 9; d++) {
                        if (s + d <= 18) {
                            compteur[i + 1][std::max(mx, d)][s + d] += compteur[i][mx][s];
                            somme[i + 1][std::max(mx, d)][s + d] += somme[i][mx][s] * 10 + compteur[i][mx][s] * d;
                        }
                    }
                }
            }
        }

        nombre_modulaire resultat(modulo, 0);
        for (size_t mx = 0; mx <= 9; mx++) {
            resultat += somme[n][mx][2 * mx];
        }
        return resultat.value();
    }
}

ENREGISTRER_PROBLEME(725, "Digit somme numbers") {
    // A number where one digit is the somme of the other digits is called a digit somme number or DS-number
    // for short. For example, 352, 3003 and 32812 are DS-numbers.
    //
    // We define S(n) to be the somme of all DS-numbers of n digits or less.
    //
    // You are given S(3) = 63270 and S(7) = 85499991450.
    //
    // Find S(2020). Give your answer modulo 10^{16}.
    std::cout << "S(3) = " << S(3, 1'000'000) << std::endl;
    std::cout << "S(7) = " << S(7, 1'000'000'000'000) << std::endl;

    size_t resultat = S(2020, 10'000'000'000'000'000);
    std::cout << "S(2020) = " << resultat << std::endl;

    return std::to_string(resultat);
}
