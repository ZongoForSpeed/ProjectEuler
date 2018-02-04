#include "problemes.h"
#include "utilitaires.h"

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(331, "Cross flips") {
    // N×N disks are placed on a square game board. Each disk has a black side and white side.
    //
    // At each turn, you may choose a disk and flip all the disks in the same row and the same column as this disk: thus
    // 2×N-1 disks are flipped. The game ends when all disks show their white side. The following example shows a game
    // on a 5×5 board.
    // 
    // It can be proven that 3 is the minimal number of turns to finish this game.
    // 
    // The bottom left disk on the N×N board has coordinates (0,0); the bottom right disk has coordinates (N-1,0) and
    // the top left disk has coordinates (0,N-1).
    //
    // Let CN be the following configuration of a board with N×N disks:
    // A disk at (x,y) satisfying p331_crossflips1.gif, shows its black side; otherwise, it shows its white side. C5 is
    // shown above.
    // 
    // Let T(N) be the minimal number of turns to finish a game starting from configuration CN or 0 if configuration CN
    // is unsolvable.
    // We have shown that T(5)=3. You are also given that T(10)=29 and T(1 000)=395253.
    //
    // Find p331_crossflips2.gif.
    nombre solution = 3;

    for (char i = 4; i <= 30; i += 2) {
        nombre n = (1 << i) - i;
        nombre x = 0, y = n - 1;
        nombre n21 = (n - 1) << 1;
        nombre r = 0; // r = x*x + y*y - (n-1)*(n-1)
        nombre compteur = 1;
        nombre odd = 0;
        char was = 0;

        while (x < y) {
            if ((x << 1) < n21 - r) // (x+1)*(x+1) + y*y < n*n
            {
                r += x;
                r += ++x;
                ++compteur;
            } else {
                char newwas;
                r -= y;
                r -= --y;
                if (r < 0) // x*x + y*y < (n-1)*(n-1)
                {
                    r += x;
                    r += ++x;
                    newwas = 0;
                } else {
                    newwas = 1;
                }

                was += newwas;

                if (compteur & 1)
                    solution += (compteur - 2 * was) << 1;
                else
                    solution -= (compteur - 2 * was) << 1;

                odd += compteur + (compteur & 1) - was;
                was = newwas;
                compteur = 1;
            }
        }

        if (x == y) //else nothing to do
        {
            if (compteur > 1) // compteur = 2 for n > 5
            {
                odd += 1 - was;
                solution += 4 * was - 1;
            } else {
                odd += 1 - was;
                solution++;
            }
        }
        solution += 2 * (odd) * (n - odd);
    }

    return std::to_string(solution);
}
