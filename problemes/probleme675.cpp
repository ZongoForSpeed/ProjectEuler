#include "problemes.h"
#include "arithmetique.h"
#include "nombre_modulaire.h"
#include "premiers.h"

typedef unsigned long long nombre;

namespace {
    nombre omega(nombre n, const std::vector<nombre> &premiers) {
        nombre resultat = 0;
        for (const auto &p: premiers) {
            if (p * p > n)
                break;
            if (n % p == 0) {
                while (n % p == 0)
                    n /= p;
                resultat++;
            }
        }
        if (n > 1)
            resultat++;

        return resultat;
    }

    nombre S(nombre n, const std::vector<nombre> &premiers) {
        nombre resultat = 0;
        auto diviseurs = arithmetique::diviseurs(n, premiers);
        for (auto d: diviseurs) {
            resultat += puissance::puissance<nombre>(2, omega(d, premiers));
        }

        return resultat;
    }

    nombre S(const std::map<nombre, nombre> &d, nombre modulo) {
        // std::map<nombre, nombre> omega{{0, 1}};
        // for (auto&[p, exposant]: d) {
        //     std::map<nombre, nombre> suivant(omega);
        //     for (auto&[w, compteur]: omega) {
        //         suivant[w + 1] += compteur * exposant;
        //     }
        //     std::swap(suivant, omega);
        // }
        //
        // nombre resultat = 0;
        // for (auto&[w, compteur]: omega) {
        //     resultat += compteur * puissance::puissance_modulaire<nombre>(2, w, modulo);
        // }
        // return resultat;
        nombre resultat = 1;

        for (auto&[p, exposant]: d) {
            resultat *= (1 + 2 * exposant);
            resultat %= modulo;
        }

        return resultat;
    }

    nombre F(nombre n, const std::vector<nombre> &premiers, nombre modulo) {
        // nombre resultat = 0;
        // for (nombre i = 2; i <= n; ++i) {
        //     resultat += S(combinatoire::factorielle(i), premiers);
        // }
        //
        // return resultat;

        std::vector<std::map<nombre, nombre>> decompositions(n + 1);
        for (auto p: premiers) {
            if (p > n) {
                break;
            }

            for (nombre f = p; f <= n; f *= p) {
                for (nombre q = f; q <= n; q += f) {
                    decompositions[q][p]++;
                }
            }
        }

        nombre_modulaire resultat(modulo, 0);
        nombre_modulaire S(modulo, 1);
        std::map<nombre, nombre> decomposition;
        for (nombre i = 2; i <= n; ++i) {
            std::map<nombre, nombre> &d = decompositions[i];
            for (auto&[p, e]: d) {
                if (auto it = decomposition.find(p); it != decomposition.end()) {
                    S /= (1 + 2 * it->second);
                    it->second += e;
                    S *= (1 + 2 * it->second);
                } else {
                    decomposition.emplace(p, e);
                    S *= (1 + 2 * e);
                }
            }

            resultat += S;
            if (i % 100'000 == 0) {
                std::cout << i << ',' << decomposition.size() << " => " << resultat << std::endl;
            }
        }

        return resultat.value();
    }
}

ENREGISTRER_PROBLEME(675, "2^ω(n)") {
    // Let ω(n) denote the number of distinct prime divisors of a positive integer n.
    // So ω(1) = 1 and ω(360) = ω(2^3 x 3² x 5) = 3.
    //
    // Let S(n) be Sum_d|n 2^ω(d).
    // E.g. S(6) = 2^ω(1) + 2^ω(1) + 2^ω(1) + 2^ω(1) = 2^0 + 2^1 + 2^1 + 2² = 9.
    //
    // Let F(n) = Sum_i=2..n S(i!). F(n) = 4821.
    //
    // Find F(10'000'000). Give your answer modulo 1'000'000'087.
    size_t modulo = 1'000'000'087;
    size_t limite = 10'000'000;
    std::vector<nombre> premiers;
    premiers::crible235<nombre>(limite, std::back_inserter(premiers));

    std::cout << "ω(1) = " << omega(1, premiers) << std::endl;
    std::cout << "ω(360) = " << omega(360, premiers) << std::endl;

    std::cout << "S(6) = " << S(6, premiers) << std::endl;
    std::map<nombre, nombre> d{{2, 1},
                               {3, 1}};
    std::cout << "S(6) = " << S(d, modulo) << std::endl;

    std::cout << "F(10) = " << F(10, premiers, modulo) << std::endl;

    nombre resultat = F(limite, premiers, modulo);
    return std::to_string(resultat);
}
