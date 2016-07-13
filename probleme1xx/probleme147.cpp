#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(147, "Rectangles in cross-hatched grids")
{
	// In a 3x2 cross-hatched grid, a total of 37 different rectangles could be situated within that
	// grid as indicated in the sketch.
    //
    // There are 5 grids smaller than 3x2, vertical and horizontal dimensions being important, i.e. 
    // 1x1, 2x1, 3x1, 1x2 and 2x2. If each of them is cross-hatched, the following number of different
    // rectangles could be situated within those smaller grids:
    //
    //      1x1: 1 
    //      2x1: 4 
    //      3x1: 8 
    //      1x2: 4 
    //      2x2: 18
    //
    // Adding those to the 37 of the 3x2 grid, a total of 72 different rectangles could be situated 
    // within 3x2 and smaller grids.
    //
    // How many different rectangles could be situated within 47x43 and smaller grids?
	nombre resultat = 0;
	
    for (nombre m = 1; m <= 43; ++m) 
	for (nombre n = 1; n <= 47; ++n) 
	{
        for (nombre x = 1; x <= m; ++x)
		for (nombre y = 1; y <= n; ++y)
		    resultat += (m-x+1) * (n-y+1);

        for (nombre x = 1; x <= 2*m; ++x)
		for (nombre y = 1; y <= 2*n; ++y)
		{
            nombre z = (x+y-1) / 2;
            nombre w = x+y-1 - z;
            if (z>m || w>m || z>n || w>n)
                continue;
            if (((x | y) & 1) == 0)
                resultat += ((m-z) * (n-z) + (m-w) * (n-w));
            else 
                resultat += ((m-z) * (n-w) + (m-w) * (n-z));
        }
    }

    return std::to_string(resultat);
}
