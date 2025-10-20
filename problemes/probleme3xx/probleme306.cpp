#include "../problemes.h"
#include "arithmetique.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(306, "Paper-strip Game") {
    // The following game is a classic example of Combinatorial Game Theory:
    // Two players start with a strip of n white squares and they take alternate turns.
    // On each turn, a player picks two contiguous white squares and paints them black.
    // The first player who cannot make a move loses.
    //
    // If n = 1, there are no valid moves, so the first player loses automatically.
    // If n = 2, there is only one valid move, after which the second player loses.
    // If n = 3, there are two valid moves, but both leave a situation where the second player loses.
    // If n = 4, there are three valid moves for the first player; she can win the game by painting the two middle
    //           squares.
    // If n = 5, there are four valid moves for the first player (shown below in red); but no matter what she does, the
    //           second player (blue) wins.
    //
    //                              R R . B B
    //                              . R R B B
    //                              B B R R .
    //                              B B . R R
    // 
    // So, for 1 ≤ n ≤ 5, there are 3 values of n for which the first player can force a win.
    // Similarly, for 1 ≤ n ≤ 50, there are 40 values of n for which the first player can force a win.
    // 
    // For 1 ≤ n ≤ 1 000 000, how many values of n are there for which the first player can force a win?
    nombre taille = 1000000;
    // https://oeis.org/A002187
    nombre lost = 1;

    if (taille > 14) ++lost;
    if (taille > 34) ++lost;

    nombre m = taille / 34;
    lost += 5 * m; // Cas perdant (reste / 34 = 5, 9, 21, 25, 29)
    for (nombre i = 34 * m; i <= taille; i++) {
        switch (i % 34) {
            case 5:
            case 9:
            case 21:
            case 25:
            case 29:
                ++lost;
                break;
            default:
                break;
        }
//        nombre ;
//        if (reste == 5 || reste == 9 || reste == 21 || reste == 25 || reste == 29)
//            ++lost;
    }

    nombre resultat = (taille - lost);
    return std::to_string(resultat);
}
