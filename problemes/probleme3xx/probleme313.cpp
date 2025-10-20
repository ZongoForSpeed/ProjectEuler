#include "../problemes.h"
#include "premiers.h"

#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(313, "Sliding game") {
    // In a sliding game a counter may slide horizontally or vertically into an empty space. The objective of the game
    // is to move the red counter from the top left corner of a grid to the bottom right corner; the space always starts
    // in the bottom right corner. For example, the following sequence of pictures show how the game can be completed in
    // five moves on a 2 by 2 grid.
    //
    // p313_sliding_game_1.gif
    //
    // Let S(m,n) represent the minimum number of moves to complete the game on an m by n grid. For example, it can be
    // verified that S(5,4) = 25.
    //
    // p313_sliding_game_2.gif
    //
    // There are exactly 5482 grids for which S(m,n) = p², where p < 100 is prime.
    //
    // How many grids does S(m,n) = p², where p < 10**6 is prime?
    nombre limite = 1000000;

    vecteur premiers;
    premiers::crible2<nombre>(limite, std::back_inserter(premiers));

    nombre resultat = 0;
    for (nombre p: premiers) {
        nombre n = (p * p + 13) / 2;
        nombre k = n / 4 + 1;
        nombre q = n - 3 * k;

        resultat += 2 * ((q + 1) / 3);

        if ((p * p + 11) % 8 == 0)
            ++resultat;
    }

    return std::to_string(resultat);
}
