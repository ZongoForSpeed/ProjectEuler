#include "problemes.h"
#include "arithmetique.h"
#include "premiers.h"
#include "racine.h"

#include <complex>

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::complex<nombre> complexe;

namespace {
    std::optional<complexe> gauss(nombre p) {
        for (nombre a = 1; 2 * a * a < p + 1; ++a) {
            nombre bb = p - a * a;
            if (auto r = racine::carre_parfait(bb)) {
                nombre b = r.value();
                if (a < b)
                    return complexe(a, b);
                else
                    return complexe(b, a);
            }
        }

        return std::nullopt;
    }

    template<typename Iterator>
    nombre algorithme(Iterator it, Iterator en, const complexe &z) {
        return it == en
               ? std::min(std::abs(z.real()), std::abs(z.imag()))
               : algorithme(std::next(it), en, z)
                 + algorithme(std::next(it), en, z * (*it))
                 + algorithme(std::next(it), en, z * std::conj(*it));
    }
}

ENREGISTRER_PROBLEME(273, "Sum of Squares") {
    // Consider equations of the form: a² + b² = N, 0 ≤ a ≤ b, a, b and N integer.
    //
    // For N=65 there are two solutions:
    // 
    // a=1, b=8 and a=4, b=7.
    // 
    // We call S(N) the sum of the values of a of all solutions of a² + b² = N, 0 ≤ a ≤ b, a, b and N integer.
    // 
    // Thus S(65) = 1 + 4 = 5.
    //
    // Find ∑S(N), for all squarefree N only divisible by primes of the form 4k+1 with 4k+1 < 150.
    const size_t taille = 150;
    vecteur premiers;
    premiers::crible2<nombre>(taille, std::back_inserter(premiers));

    premiers.erase(std::remove_if(premiers.begin(),
                                  premiers.end(),
                                  [](nombre p) { return p % 4 != 1; }),
                   premiers.end());

    std::vector<complexe> racines;
    for (auto p: premiers) {
        if (auto z = gauss(p))
            racines.push_back(*z);
    }

    // std::cout << premiers << std::endl;
    // std::cout << racines << std::endl;

    nombre resultat = 0;
    for (auto it = racines.begin(), en = racines.end(); it != en; ++it) {
        resultat += algorithme(std::next(it), en, *it);
    }

    return std::to_string(resultat);
}
