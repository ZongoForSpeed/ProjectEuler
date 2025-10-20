#include "../problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(335, "Gathering the beans") {
    // Whenever Peter feels bored, he places some bowls, containing one bean each, in a circle. After this, he takes all
    // the beans out of a certain bowl and drops them one by one in the bowls going clockwise. He repeats this, starting
    // from the bowl he dropped the last bean in, until the initial situation appears again. For example with 5 bowls he
    // acts as follows:
    //
    // p335_mancala.gif
    // So with 5 bowls it takes Peter 15 moves to return to the initial situation.
    //
    // Let M(x) represent the number of moves required to return to the initial situation, starting with x bowls. Thus,
    // M(5) = 15. It can also be verified that M(100) = 10920.
    //
    //Find p335_sum.gifM(2k+1). Give your answer modulo 79.
    const auto modulo = puissance::puissance<nombre>(7, 9);
    const nombre phi = 6 * puissance::puissance<nombre>(7, 8);
    const auto limite = puissance::puissance<nombre>(10, 18);

    nombre puissance2 = 2;
    nombre puissance3 = 1;
    nombre puissance4 = 1;

    nombre resultat = 0;
    for (size_t k = 0; k < phi; ++k) {
        nombre m = modulo + puissance4 + puissance2 - puissance3;
        m %= modulo;
        m *= (limite - k) / phi + 1;
        m %= modulo;

        resultat += m;
        resultat %= modulo;

        puissance2 *= 2;
        puissance3 *= 3;
        puissance4 *= 4;

        puissance2 %= modulo;
        puissance3 %= modulo;
        puissance4 %= modulo;
    }

    return std::to_string(resultat);
}
