#include "problemes.h"
#include "arithmetique.h"
#include "iterator.h"

#include <fstream>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(126, "Cuboid layers") {
    // The minimum number of cubes to cover every visible face on a cuboid measuring 3 x 2 x 1 is twenty-two.
    //
    // If we then add a second layer to this solid it would require forty-six cubes to cover every visible face, the
    // third layer would require seventy-eight cubes, and the fourth layer would require one-hundred and eighteen cubes
    // to cover every visible face.
    //
    // However, the first layer on a cuboid measuring 5 x 1 x 1 also requires twenty-two cubes; similarly the first
    // layer on cuboids measuring 5 x 3 x 1, 7 x 2 x 1, and 11 x 1 x 1 all contain forty-six cubes.
    // 
    // We shall define C(n) to represent the number of cuboids that contain n cubes in one of its layers. So C(22) = 2,
    // C(46) = 4, C(78) = 5, and C(118) = 8.
    //
    // It turns out that 154 is the least value of n for which C(n) = 10.
    // 
    // Find the least value of n for which C(n) = 1000.
    nombre limite = 100000;
    vecteur couche(limite, 0);

    for (nombre a = 1; 4 * a < limite; ++a)
        for (nombre b = 1; b <= a && 4 * a * b < limite; ++b)
            for (nombre c = 1; c <= b; ++c) {
                nombre n = 1;
                nombre layer = 2 * (a * b + b * c + a * c);
                if (layer >= limite)
                    break;
                while (layer < limite) {
                    couche[layer]++;
                    ++n;
                    layer += 4 * (a + b + c) + 8 * (n - 2);
                }
            }

    auto it = std::ranges::find(couche, 1000);

    nombre resultat = iterator::distance(couche.begin(), it);
    return std::to_string(resultat);
}
