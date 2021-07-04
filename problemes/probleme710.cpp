#include "problemes.h"
#include "numerique.h"
#include "utilitaires.h"
#include "premiers.h"
#include "timer.h"
#include "nombre_modulaire.h"

ENREGISTRER_PROBLEME(710, "One Million Members") {
    // On Sunday 5 April 2020 the Project Euler membership first exceeded one million members. We would like to present
    // this problem to celebrate that milestone. Thank you to everyone for being a part of Project Euler.
    //
    // The number 6 can be written as a palindromic sum in exactly eight different ways:
    // (1, 1, 1, 1, 1, 1), (1, 1, 2, 1, 1), (1, 2, 2, 1), (1, 4, 1), (2, 1, 1, 2), (2, 2, 2), (3, 3), (6)
    //
    // We shall define a <dfn>twopal</dfn> to be a palindromic tuple having at least one element with a value of 2.
    // It should also be noted that elements are not restricted to single digits. For example, (3, 2, 13, 6, 13, 2, 3)
    // is a valid twopal.
    //
    // If we let $t(n)$ be the number of twopals whose elements sum to n, then it can be seen that t(6) = 4:
    // (1, 1, 2, 1, 1), (1, 2, 2, 1), (2, 1, 1, 2), (2, 2, 2)
    //
    // Similarly, t(20) = 824.
    //
    // In searching for the answer to the ultimate question of life, the universe, and everything, it can be verified
    // that t(42) = 1999923, which happens to be the first value of $t(n)$ that exceeds one million.
    //
    // However, your challenge to the "ultimatest" question of life, the universe, and everything is to find the least
    // value of n >= 42 such that t(n) is divisible by one million.
    size_t limite = 2'000'000;

    std::vector<nombre_modulaire> T(limite, nombre_modulaire(1'000'000, 0));
    std::vector<nombre_modulaire> S(limite, nombre_modulaire(1'000'000, 0));

    T[1] = 1;
    T[2] = 2;
    S[1] = 1;
    S[2] = 3;

    const nombre_modulaire deux(1'000'000, 2);

    size_t resultat = 0;

    for (size_t n = 3; n < limite; ++n) {
        T[n] = S[n - 1] + nombre_modulaire::puissance(deux, n - 2) - T[n - 2];
        S[n] = S[n - 1] + T[n];
        if (T[n].value() == 0) {
            resultat = 2*n;
            break;
        }
    }

    std::cout << "t(20) = " << T[20 / 2] << std::endl;
    std::cout << "t(42) = " << T[42 / 2] << std::endl;

    return std::to_string(resultat);
}
