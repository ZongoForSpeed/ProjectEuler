#include "problemes.h"
#include "utilitaires.h"
#include "grand_nombre.h"

ENREGISTRER_PROBLEME(117, "Red, green, and blue tiles")
{
    // Using a combination of black square tiles and oblong tiles chosen from: red tiles measuring 
    // two units, green tiles measuring three units, and blue tiles measuring four units, it is 
    // possible to tile a row measuring five units in length in exactly fifteen different ways.
    //
    // How many ways can a row measuring fifty units in length be tiled?
    // 
    // NOTE: This is related to Problem 116.
    size_t longueur = 50;
    grand_nombre resultat = 0;
    
    for (size_t s4 = 0; s4 < longueur + 1; s4 += 4)
    for (size_t s3 = 0; s3 < longueur - s4 + 1; s3 += 3)
    for (size_t s2 = 0; s2 < longueur - s3 - s4 + 1; s2 += 2)
    {
        size_t n4 = s4 / 4;
        size_t n3 = s3 / 3;
        size_t n2 = s2 / 2;
        size_t n1 = longueur - s2 - s3 - s4;
        
        grand_nombre n = grand_nombre::factorielle(n1 + n2 + n3 + n4);
        grand_nombre d = grand_nombre::factorielle(n1) * grand_nombre::factorielle(n2)
            * grand_nombre::factorielle(n3) * grand_nombre::factorielle(n4);
            
        resultat += n/d;
    }

    return resultat.to_string();
}
