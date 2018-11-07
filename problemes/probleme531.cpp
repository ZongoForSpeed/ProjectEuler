#include "problemes.h"
#include "utilitaires.h"
#include "arithmetique.h"

#include "premiers.h"
#include "arithmetique_modulaire.h"

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

namespace {


    nombre g(nombre a, const std::map<nombre, size_t> &factorisation_n, nombre b,
             const std::map<nombre, size_t> &factorisation_m) {
        std::map<nombre, std::pair<nombre, nombre>> equation;
        for (const auto &e: factorisation_n) {
            nombre d = puissance::puissance(e.first, e.second);
            nombre value = a % d;
            equation[e.first] = std::make_pair(value, d);
        }

        for (const auto &e: factorisation_m) {
            nombre d = puissance::puissance(e.first, e.second);
            nombre value = b % d;
            auto it = equation.find(e.first);
            if (it != equation.end()) {
                nombre prev_value, prev_d;
                std::tie(prev_value, prev_d) = it->second;
                if (prev_d == d) {
                    if (prev_value != value) {
                        return 0;
                    }
                } else if (prev_d > d) {
                    if (prev_value % d != value) {
                        return 0;
                    }
                } else if (prev_value != value % prev_d) {
                    return 0;
                } else {
                    equation[e.first] = std::make_pair(value, d);
                }
            } else {
                equation[e.first] = std::make_pair(value, d);
            }
        }

        vecteur restes;
        vecteur modulos;
        for (const auto &e: equation) {
            restes.push_back(e.second.first);
            modulos.push_back(e.second.second);
        }

        return arithmetique_modulaire::restes_chinois<nombre>(modulos, restes);
    }
}

ENREGISTRER_PROBLEME(531, "Chinese leftovers") {
    // Let g(a,n,b,m) be the smallest non-negative solution x to the system:
    // x ≡ a mod n
    // x ≡ b mod m
    // if such a solution exists, otherwise 0.
    // e.g. g(2,4,4,6)=10, but g(3,4,4,6)=0.
    //
    // Let φ(n) be Euler's totient function.
    // Let f(n,m)=g(φ(n),n,φ(m),m)
    //
    // Find ∑f(n,m) for 1000000 ≤ n < m < 1005000
    vecteur premiers;
    premiers::crible235<nombre>(1005000, std::back_inserter(premiers));

    nombre resultat = 0;
    for (nombre n = 1000000; n < 1005000; ++n) {
        std::map<nombre, size_t> factorisation_n;
        arithmetique::decomposition(n, premiers, factorisation_n);

        nombre phi_n = arithmetique::phi(n, premiers);
        for (nombre m = n + 1; m < 1005000; ++m) {
            std::map<nombre, size_t> factorisation_m;
            arithmetique::decomposition(m, premiers, factorisation_m);

            nombre phi_m = arithmetique::phi(m, premiers);
            nombre f = g(phi_n, factorisation_n, phi_m, factorisation_m);
            resultat += f;
        }
    }

    return std::to_string(resultat);
}
