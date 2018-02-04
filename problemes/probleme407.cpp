#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "chiffres.h"

namespace {
    size_t M(const std::vector<size_t> &premiers, size_t n) {
        std::map<size_t, size_t> facteurs;
        arithmetiques::decomposition(n, premiers, facteurs);
        std::vector<size_t> modulos;
        for (auto &f: facteurs) {
            modulos.push_back(puissance::puissance(f.first, f.second));
        }
        size_t N = (1 << facteurs.size());
        size_t resultat = 0;
        for (size_t t = 1; t < N; ++t) {
            auto restes = chiffres::extraire_chiffres(t, 2);
            if (restes.size() < facteurs.size())
                restes.insert(restes.begin(), facteurs.size() - restes.size(), 0);
            
            // std::cout << restes << std::endl;
            size_t r = arithmetiques::restes_chinois<size_t>(modulos, restes, premiers);
            resultat = std::max(r, resultat);
        }
        
        return resultat;
    }
}

ENREGISTRER_PROBLEME(407, "Idempotents") {
    // If we calculate a² mod 6 for 0 ≤ a ≤ 5 we get: 0,1,4,3,4,1.
    //
    // The largest value of a such that a² ≡ a mod 6 is 4.
    // Let's call M(n) the largest value of a < n such that a² ≡ a (mod n).
    // So M(6) = 4.
    //
    // Find ∑M(n) for 1 ≤ n ≤ 10**7.
    size_t limite = 10'000'000;
    
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite, std::back_inserter(premiers));
    
    size_t resultat = 0;
    std::cout << "M(6) = " << M(premiers, 6) << std::endl;
    
    for (size_t n = 2; n < limite + 1; ++n) {
        // std::cout << n << std::endl;
        resultat += M(premiers, n);
    }
    
    return std::to_string(resultat);
}
