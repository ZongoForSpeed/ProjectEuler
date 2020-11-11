#include "problemes.h"
#include "arithmetique.h"
#include "nombre_modulaire.h"
#include "timer.h"
#include "premiers.h"

typedef unsigned long long nombre;

namespace {
    nombre I(nombre n) {
        for (nombre i = n - 2; i > 0; --i) {
            if ((i * i) % n == 1) {
                return i;
            }
        }

        return 0;
    }

    nombre S(nombre n) {
        nombre resultat = 0;
        for (nombre i = 3; i <= n; ++i) {
            resultat += I(i);
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(451, "Modular inverses") {
    // Consider the number 15.
    //
    // There are eight positive numbers less than 15 which are coprime to 15: 1, 2, 4, 7, 8, 11, 13, 14.
    //
    // The modular inverses of these numbers modulo 15 are: 1, 8, 4, 13, 2, 11, 7, 14 because
    // 1 · 1 mod 15=1
    // 2 · 8=16 mod 15=1
    // 4 · 4=16 mod 15=1
    // 7 · 13=91 mod 15=1
    // 11 · 11=121 mod 15=1
    // 14 · 14=196 mod 15=1
    //
    // Let I(n) be the largest positive number m smaller than n-1 such that the modular inverse of m modulo n equals m itself.
    //
    // So I(15)=11.
    //
    // Also I(100)=51 and I(7)=1.
    //
    // Find ∑ I(n) for 3 ≤ n ≤ 2×10^7
    std::cout << "I(15) = " << I(15) << std::endl;
    std::cout << "I(100) = " << I(100) << std::endl;
    std::cout << "I(7) = " << I(7) << std::endl;
    std::cout << "S(100) = " << S(100) << std::endl;

    nombre limite = 20'000'000;

    std::vector<nombre> facteur_premier(limite + 1);

    std::iota(facteur_premier.begin(), facteur_premier.end(), 0ull);
    for (nombre p = 2; p <= limite; ++p) {
        if (facteur_premier[p] == p) {
            for (nombre q = p * p; q <= limite; q += p) {
                facteur_premier[q] = std::min(p, facteur_premier[q]);
            }
        }
    }

    std::vector<std::vector<nombre>> solutions(limite + 1);
    solutions[2].push_back(1);

    nombre resultat = 0;
    for (nombre n = 3; n <= limite; ++n) {
        auto &solution_n = solutions[n];
        nombre p = facteur_premier[n];
        if (n == p) {
            // n est premier les solutions sont de la forme 1 et p-1;
            solution_n.push_back(1);
            solution_n.push_back(p - 1);

            // std::cout << "I(" << p << ") = " << solution_n << std::endl;
            resultat += 1;
        } else {
            // n est composite de la forme p*q (premier) les solutions sont de la forme
            // q' + k * q (où q' solutions de q et k=1..p-1)
            nombre q = n / p;
            auto &solution_q = solutions[q];
            for (nombre i = 0; i < n; i += q) {
                for (nombre j : solution_q) {
                    nombre k = i + j;
                    if ((k * k) % n == 1) {
                        solution_n.push_back(k);
                    }
                }
            }

            // std::cout << "I(" << n << ") = " << solution_n << std::endl;
            resultat += *(std::next(solution_n.rbegin()));
        }
    }

    return std::to_string(resultat);
}
