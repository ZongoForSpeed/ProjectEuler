#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "polygonal.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(173, "Using up to one million tiles how many different \"hollow\" square laminae can be formed?")
{
    // We shall define a square lamina to be a square outline with a square "hole" so that the shape 
    // possesses vertical and horizontal symmetry. For example, using exactly thirty-two square tiles 
    // we can form two different square laminae:
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
    // With one-hundred tiles, and not necessarily using all of the tiles at one time, it is possible
    // to form forty-one different square laminae.
    //
    // Using up to one million tiles how many different square laminae can be formed?
    nombre limite = 1000000;
    nombre resultat = 0;
    for (nombre n = 1; 2*n - 1 < limite; ++n)
        resultat += (racine_carre(n*n + limite) - n) / 2;

    return std::to_string(resultat);
}
