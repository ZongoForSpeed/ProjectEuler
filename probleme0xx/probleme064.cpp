#include "problemes.h"
#include "polygonal.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(64, "Odd period square roots") {
    // It can be seen that the sequence is repeating. For conciseness, we use the notation √23 = [4;(1,3,1,8)], to
    // indicate that the block (1,3,1,8) repeats indefinitely.
    // 
    // The first ten continued fraction representations of (irrational) square roots are:
    // 
    // √2=[1;(2)], period=1
    // √3=[1;(1,2)], period=2
    // √5=[2;(4)], period=1
    // √6=[2;(2,4)], period=2
    // √7=[2;(1,1,1,4)], period=4
    // √8=[2;(1,4)], period=2
    // √10=[3;(6)], period=1
    // √11=[3;(3,6)], period=2
    // √12= [3;(2,6)], period=2
    // √13=[3;(1,1,1,1,6)], period=5
    // 
    // Exactly four continued fractions, for N ≤ 13, have an odd period.
    // 
    // How many continued fractions for N ≤ 10000 have an odd period?
    auto periode = [](nombre r) -> nombre {
        if (polygonal::est_carre(r))
            return 0;

        nombre p = racine_carre(r);
        nombre q = 1;

        std::map<std::pair<nombre, nombre>, nombre> restes;
        nombre n = 1;
        while (true) {
            q = (r - (p * p)) / q;
            nombre f = static_cast<nombre>(floor((racine_carre(r) + p) / (1.0 * q)));
            p = -(p - (f * q));
            auto it = restes.find(std::make_pair(p, q));
            if (it != restes.end())
                return n - it->second;
            restes[std::make_pair(p, q)] = n;
            ++n;
        }
    };

    nombre resultat = 0;
    for (nombre n = 1; n <= 10000; ++n) {
        if (periode(n) % 2 == 1)
            ++resultat;
    }
    return std::to_string(resultat);
}
