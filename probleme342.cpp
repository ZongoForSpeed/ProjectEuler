#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "multidimension.h"
#include "mp_nombre.h"

namespace {
    template<typename Iterateur>
    size_t algorithme(Iterateur debut, Iterateur fin, size_t courant, mp_nombre phi, size_t limite) {
        size_t resultat = 0;
        if (courant != 1 && mp_nombre::racine_parfaite(phi, 3)) {
            resultat += courant;
        }
        for (Iterateur it = debut; it != fin; ++it) {
            size_t p = *it;
            if (courant * p > limite || courant * p * p > limite)
                break;
            mp_nombre y = phi * (p - 1) * p;
            for (size_t x = courant * p; x <= limite; x *= p, y *= p * p) {
                resultat += algorithme(std::next(it), fin, x, y, limite);
            }
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(342, "The totient of a square is a cube")
{
    // Consider the number 50.
    // 50² = 2500 = 22 × 54, so φ(2500) = 2 × 4 × 53 = 8 × 53 = 23 × 53.
    // So 2500 is a square and φ(2500) is a cube.
    //
    // Find the sum of all numbers n, 1 < n < 10**10 such that φ(n²) is a cube.
    //
    // φ denotes Euler's totient function.
    const size_t limite = 10'000'000'000;
    const size_t limite_crible = 1'000'000;
    
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite_crible, std::back_inserter(premiers));
    
    size_t resultat = algorithme(premiers.begin(), premiers.end(), 1, 1, limite);

    return std::to_string(resultat);
}
