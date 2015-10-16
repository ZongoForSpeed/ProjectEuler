#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(166)
{
    Timer timer("probleme 166");
    // A 4x4 grid is filled with digits d, 0 ≤ d ≤ 9.
    //
    // It can be seen that in the grid
    //
    //                                       6 3 3 0
    //                                       5 0 4 3
    //                                       0 7 1 4
    //                                       1 2 4 5
    //
    // the sum of each row and each column has the value 12. Moreover the sum of each diagonal is 
    // also 12.
    //
    // In how many ways can you fill a 4x4 grid with the digits d, 0 ≤ d ≤ 9 so that each row, each
    // column, and both diagonals have the same sum?
    nombre resultat = 0;
    for (short a11 = 0; a11 < 10; ++a11)
    for (short a12 = 0; a12 < 10; ++a12)
    for (short a13 = 0; a13 < 10; ++a13)
    for (short a14 = 0; a14 < 10; ++a14)
    {
        short d = a11 + a12 + a13 + a14;
        for (short a21 = 0; a21 < 10; ++a21)
        for (short a22 = 0; a22 < 10; ++a22)
        for (short a23 = 0; a23 < 10; ++a23)
        {
            short a24 = d - (a21 + a22 + a23);
            if (a24 < 10 && a24 >= 0)
            for (short a31 = 0; a31 < 10; ++a31)
            {
                short a41 = d - (a11 + a21 + a31);
                if (a41 < 10 && a41 >= 0)
                {
                    short a32 = d - (a41 + a23 + a14);
                    if (a32 < 10 && a32 >= 0 && (a32 + a23 + a14) == (a11 + a21 + a31))
                    {
                        short a42 = d - (a12 + a22 + a32);
                        if (a42 < 10 && a42 >= 0)
                        for (short a33 = 0; a33 < 10; ++a33)
                        {
                            if (d >= (a31 + a32 + a33) && d >= (a13 + a23 + a33))
                            {
                                short a34 = d - (a31 + a32 + a33);
                                short a43 = d - (a13 + a23 + a33);
                                if (a34 < 10 && a34 >= 0 && a43 < 10 && a43 >= 0
                                    && (a41 + a42 + a43) == (a11 + a22 + a33) 
                                    && (a41 + a42 + a43) == (a14 + a24 + a34))
                                {
                                    short a44 = d - (a41 + a42 + a43);
                                    if (a44 < 10 && a44>= 0)
                                        ++resultat;
                                }
                            }
                        }
                        
                    }
                }
                
            }
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}
