#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(114, "Counting block combinations I")
{
    // A row measuring seven units in length has red blocks with a minimum length of three units 
    // placed on it, such that any two red blocks (which are allowed to be different lengths) are
    // separated by at least one black square. There are exactly seventeen ways of doing this.
    //
    // How many ways can a row measuring fifty units in length be filled?
    //
    // NOTE: Although the example above does not lend itself to the possibility, in general it is 
    // permitted to mix block sizes. For example, on a row measuring eight units in length you could
    // use red (3), black (1), and red (4).
    nombre limite = 50;
    vecteur valeur { 1, 1, 1, 2 };
    for (nombre n = 4; n <= limite; ++n)
    {
        valeur.push_back(2*valeur.back() - valeur.at(n - 2) + valeur.at(n - 4));
    }
    
    return std::to_string(valeur.back());
}
