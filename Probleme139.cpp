#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(139)
{
    Timer t("probleme 139");
    // Let (a, b, c) represent the three sides of a right angle triangle with integral length sides. 
    // It is possible to place four such triangles together to form a square with length c.
    //
    // For example, (3, 4, 5) triangles can be placed together to form a 5 by 5 square with a 1 by 1 
    // hole in the middle and it can be seen that the 5 by 5 square can be tiled with twenty-five 
    // 1 by 1 squares.
    //
    // However, if (5, 12, 13) triangles were used then the hole would measure 7 by 7 and these could 
    // not be used to tile the 13 by 13 square.
    //
    // Given that the perimeter of the right triangle is less than one-hundred million, how many 
    // Pythagorean triangles would allow such a tiling to take place?
    nombre limite = 100000000;
	nombre borne = std::sqrt(limite / 2 + 1) + 1;

    nombre resultat = 0;
	for (nombre m = 2; m < borne; ++m)
	{
		// a = m^2 - n^2 ,\ \, b = 2mn ,\ \, c = m^2 + n^2 
		for (nombre n = 1; n < m; ++n)
		{
			nombre mn = m - n;
			if (mn%2 != 0 && arithmetiques::PGCD(m, n) == 1)
			{
                nombre a = m*m - n*n;
                nombre b = 2*m*n;
                nombre c = m*m + n*n;
                
                if (a > b) std::swap(a, b);
                
                nombre abc = a+b+c;
                nombre ba = (b - a);
                if (abc < limite && c%ba == 0)
                	resultat += limite / abc;
			}
		}
	}
    
    std::cout << "Solution: " << resultat << std::endl;
}

