#include "problemes.h"
#include "arithmetiques.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(174,
                     "Counting the number of \"hollow\" square laminae that can form one, two, three, ... distinct arrangements") {
    // We shall define a square lamina to be a square outline with a square "hole" so that the shape possesses vertical
    // and horizontal symmetry.
    //
    // Given eight tiles it is possible to form a lamina in only one way: 3x3 square with a 1x1 hole in the middle.
    // However, using thirty-two tiles it is possible to form two distinct laminae.
    //
    //              XXXXXX  XXXXXXXXX
    //              XXXXXX  X       X
    //              XX  XX  X       X
    //              XX  XX  X       X
    //              XXXXXX  X       X
    //              XXXXXX  X       X
    //                      X       X
    //                      X       X
    //                      XXXXXXXXX
    //
    // If t represents the number of tiles used, we shall say that t = 8 is type L(1) and t = 32 is type L(2).
    //
    // Let N(n) be the number of t ≤ 1000000 such that t is type L(n); for example, N(15) = 832.
    //
    // What is ∑ N(n) for 1 ≤ n ≤ 10? We shall define a square lamina to be a square outline with a square "hole" so
    // that the shape
    nombre limite = 1000000;
    nombre resultat = 0;
    for (nombre n = 4; n < limite + 1; n += 4) {
        nombre compteur = 0;
        for (nombre d = 2; d * d < n; d += 2) {
            if (n % (2 * d) == 0)
                ++compteur;
        }

        if (0 < compteur && compteur < 11)
            ++resultat;
    }

    return std::to_string(resultat);
}
