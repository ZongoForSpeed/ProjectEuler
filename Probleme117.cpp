#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

void probleme117()
{
    Timer t("probleme 117");
    // Using a combination of black square tiles and oblong tiles chosen from: red tiles measuring 
    // two units, green tiles measuring three units, and blue tiles measuring four units, it is 
    // possible to tile a row measuring five units in length in exactly fifteen different ways.
    //
    // How many ways can a row measuring fifty units in length be tiled?
    // 
    // NOTE: This is related to Problem 116.
    nombre longueur = 50;
    nombre resultat = 0;
    
    for (nombre s4 = 0; s4 < longueur + 1; s4 += 4)
    for (nombre s3 = 0; s3 < longueur - s4 + 1; s3 += 3)
    for (nombre s2 = 0; s2 < longueur - s3 - s4 + 1; s2 += 2)
    {
        nombre n4 = s4 / 4;
        nombre n3 = s3 / 3;
        nombre n2 = s2 / 2;
        nombre n1 = longueur - s2 - s3 - s4;
        
        nombre n = combinatoire::factorielle<nombre>(n1 + n2 + n3 + n4);
        nombre d = combinatoire::factorielle<nombre>(n1) * combinatoire::factorielle<nombre>(n2) 
            * combinatoire::factorielle<nombre>(n3) * combinatoire::factorielle<nombre>(n4);
            
        resultat += n/d;
    }

    std::cout << "Solution: " << resultat << std::endl;
}
