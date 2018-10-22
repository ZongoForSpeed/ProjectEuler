#include "problemes.h"
#include "utilitaires.h"
#include "matrice.h"
#include "puissance.h"

#include <boost/multiprecision/cpp_bin_float.hpp>

typedef boost::multiprecision::cpp_bin_float_quad mp_float;
typedef boost::multiprecision::cpp_int mp_nombre;

typedef long long int nombre;
typedef std::vector<mp_nombre> vecteur;

namespace {
    const mp_float phi = (1 + boost::multiprecision::sqrt(mp_float(5))) / 2;

    nombre division(mp_nombre n, mp_float d) {
        mp_float q = n.convert_to<nombre>() / d;
        return q.convert_to<nombre>();
    }

    mp_nombre somme_entier(mp_nombre n) {
        return n * (n + 1) / 2;
    }

    mp_nombre somme_carre(mp_nombre n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    mp_nombre somme_triangle(mp_nombre n) {
        return (somme_carre(n) + somme_entier(n)) / 2;
    }

    std::pair<mp_nombre, mp_nombre> LU(mp_nombre n) {
        if (n < 3) {
            return std::make_pair(0, 0);
        }

        mp_nombre m = division(n, phi);
        mp_nombre L0, U0;
        std::tie(L0, U0) = LU(m);
        mp_nombre U1 = somme_carre(m) - somme_entier(m) - U0 - L0;
        mp_nombre L1 = U1 + somme_triangle(m - 1) - L0;
        mp_nombre L2 = somme_carre(n - m - 1) + (m + 1) * somme_entier(n - m - 1);
        mp_nombre U2 = n * somme_entier(n - m - 1) - somme_carre(n - m - 1);
        return std::make_pair(L0 + L1 + L2, U0 + U1 + U2);
    }

    mp_nombre S(mp_nombre n) {
        mp_nombre L, U;
        std::tie(L, U) = LU(n);
        return L + U;
    }
}

ENREGISTRER_PROBLEME(325, "Stone Game II") {
    // A game is played with two piles of stones and two players. At her turn, a player removes a number of stones from 
    // the larger pile. The number of stones she removes must be a positive multiple of the number of stones in the 
    // smaller pile.
    //
    // E.g., let the ordered pair(6,14) describe a configuration with 6 stones in the smaller pile and 14 stones in the
    // larger pile, then the first player can remove 6 or 12 stones from the larger pile.
    //
    // The player taking all the stones from a pile wins the game.
    //
    // A winning configuration is one where the first player can force a win. For example, (1,5), (2,6) and (3,12) are
    // winning configurations because the first player can immediately remove all stones in the second pile.
    //
    // A losing configuration is one where the second player can force a win, no matter what the first player does. 
    // For example, (2,3) and (3,4) are losing configurations: any legal move leaves a winning configuration for the 
    // second player.
    //
    // Define S(N) as the sum of (xi+yi) for all losing configurations (xi,yi), 0 < xi < yi ≤ N. We can verify that 
    // S(10) = 211 and S(10^4) = 230312207313.
    //
    // Find S(10^16) mod 7^10.
    nombre N = puissance::puissance<nombre>(10, 16u);
    nombre modulo = puissance::puissance<nombre>(7, 10u);
    std::cout << "S(10) = " << S(10) << std::endl;
    std::cout << "S(10000) = " << S(10000) << std::endl;
    mp_nombre resultat = S(N);
    resultat %= modulo;
    return resultat.str();
}
