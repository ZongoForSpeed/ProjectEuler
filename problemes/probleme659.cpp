#include <maths/arithmetique_modulaire.h>
#include "problemes.h"
#include "premiers.h"
#include "random.h"

namespace {

    size_t calcul_racine(size_t p) {
        std::mt19937& mt = utilitaires::generator();
        std::uniform_int_distribution<size_t> distribution(1, p - 2);
        size_t exp = p - 1;
        while (exp % 2 == 0) {
            exp /= 2;
        }
        size_t i = 1;
        while (i == 1 || i == p - 1) {
            i = puissance::puissance_modulaire(distribution(mt), exp, p);
        }
        while (true) {
            size_t const r = puissance::puissance_modulaire(i, 2, p);
            if (r == p - 1) {
                return i;
            }
            i = r;
        }

    }

}

ENREGISTRER_PROBLEME(659, "Largest prime") {
    // Consider the sequence n² + 3 with n >= 1.
    //
    // If we write down the first terms of this sequence we get:
    // 4, 7, 12, 19, 28, 39, 52, 67, 84, 103, 124, 147, 172, 199, 228, 259, 292, 327, 364, ...
    //
    // We see that the terms for n=6 and n=7 (39 and 52) are both divisible by 13.
    //
    // In fact 13 is the largest prime dividing any two successive terms of this sequence.
    //
    //Let P(k) be the largest prime that divides any two successive terms of the sequence n² + k².
    //
    //Find the last 18 digits of Sum_k=1..10'000'000 P(k).
    size_t modulo = 1'000'000'000'000'000'000;
    size_t limite = 10'000'000;

    std::vector<size_t> premiers;
    premiers::crible235<size_t>(2 * limite, std::back_inserter(premiers));

    std::vector<size_t> facteurs(limite + 1, 0);
    for (size_t k = 1; k <= limite; k++)
        facteurs[k] = 4 * k * k + 1;

    for (size_t p: premiers) {
        if (p % 4 != 1) {
            continue;
        }

        size_t i = calcul_racine(p);
        for (size_t k = (p / 2 * i) % p; k <= limite; k += p) {
            while (facteurs[k] > p && facteurs[k] % p == 0) facteurs[k] /= p;
        }

        for (size_t k = (p * p - p / 2 * i) % p; k <= limite; k += p) {
            while (facteurs[k] > p && facteurs[k] % p == 0) facteurs[k] /= p;
        }
    }
    size_t resultat = 0;

    for (size_t f: facteurs) {
        resultat += f;
        resultat %= modulo;
    }

    return std::to_string(resultat);
}
