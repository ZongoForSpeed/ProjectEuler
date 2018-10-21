#include "problemes.h"
#include "utilitaires.h"
#include "combinatoire.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(117, "Red, green, and blue tiles") {
    // Using a combination of black square tiles and oblong tiles chosen from: red tiles measuring two units, green
    // tiles measuring three units, and blue tiles measuring four units, it is possible to tile a row measuring five
    // units in length in exactly fifteen different ways.
    //
    // How many ways can a row measuring fifty units in length be tiled?
    // 
    // NOTE: This is related to Problem 116.
    unsigned long longueur = 50;
    nombre resultat = 0;

    for (unsigned long s4 = 0; s4 < longueur + 1; s4 += 4)
        for (unsigned long s3 = 0; s3 < longueur - s4 + 1; s3 += 3)
            for (unsigned long s2 = 0; s2 < longueur - s3 - s4 + 1; s2 += 2) {
                unsigned long n4 = s4 / 4;
                unsigned long n3 = s3 / 3;
                unsigned long n2 = s2 / 2;
                unsigned long n1 = longueur - s2 - s3 - s4;

                nombre n = combinatoire::factorielle<nombre>(n1 + n2 + n3 + n4);
                nombre d = combinatoire::factorielle<nombre>(n1) * combinatoire::factorielle<nombre>(n2)
                              * combinatoire::factorielle<nombre>(n3) * combinatoire::factorielle<nombre>(n4);

                resultat += n / d;
            }

    return resultat.str();
}
