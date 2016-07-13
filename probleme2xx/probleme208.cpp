#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "multidimension.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(208, "Robot Walks")
{
    // A robot moves in a series of one-fifth circular arcs (72°), with a free choice of a clockwise
    // or an anticlockwise arc for each step, but no turning on the spot.
    //    
    // One of 70932 possible closed paths of 25 arcs starting northward is
    //
    // Given that the robot starts facing North, how many journeys of 70 arcs in length can it take
    // that return it, after the final arc, to its starting position?
    // (Any arc may be traversed multiple times.)
	nombre maximum = 14;
    multidimension<nombre, 2> choix(maximum, maximum, 0UL);
    
    choix[0][0] = 1;
    for (nombre i = 1; i < maximum; ++i)
    {
        choix[i][0] = 1;
        choix[i][i] = 1;
    }
    for (nombre i = 1; i < maximum; ++i)
    for (nombre j = 1; j < i; ++j)
		choix[i][j] = choix[i - 1][j - 1] + choix[i - 1][j];
		
	nombre resultat = 0;
	auto choix_max = choix.back();
	for (nombre n = 0; n < maximum; ++n)
    {
        resultat += puissance::puissance(choix_max[n], 5);
        if (n > 0)
        {
            resultat += puissance::puissance(choix_max[n], 4)
                        * puissance::puissance(choix_max[n - 1], 1);
            resultat += puissance::puissance(choix_max[n], 3)
                        * puissance::puissance(choix_max[n - 1], 2);
            resultat += puissance::puissance(choix_max[n], 2)
                        * puissance::puissance(choix_max[n - 1], 3);
            resultat += puissance::puissance(choix_max[n], 1)
                        * puissance::puissance(choix_max[n - 1], 4);
        }
    }

    return std::to_string(2 * resultat);
}
