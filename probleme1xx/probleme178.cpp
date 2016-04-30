#include "problemes.h"
#include "arithmetiques.h"
#include "multidimension.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(178, "Step Numbers")
{
    // Consider the number 45656. 
    // It can be seen that each pair of consecutive digits of 45656 has a difference of one.
    // A number for which every pair of consecutive digits has a difference of one is called a step 
    // number.
    // A pandigital number contains every decimal digit from 0 to 9 at least once.
    // How many pandigital step numbers less than 1040 are there?
    multidimension<nombre, 4> f(41UL, 10UL, 10UL, 10UL, 0UL);

    for (nombre i = 0; i < 10; ++i)
        f[1][i][i][i] = 1;

    for(nombre m = 2; m<=40; m++)
    for(nombre x = 0; x < 10; x++)
    for(nombre y = x+1; y < 10; y++)
    for(nombre z = x; z<=y; z++)
    {
        if(z>x && z<y)
            f[m][x][y][z]=f[m-1][x][y][z-1]+f[m-1][x][y][z+1];
        if(z==x)
            f[m][x][y][z]=f[m-1][x][y][x+1]+f[m-1][x+1][y][x+1];
        if(z==y)
            f[m][x][y][z]=f[m-1][x][y][y-1]+f[m-1][x][y-1][y-1];
    }
    
    nombre resultat=0;
    for(nombre i=1;i<=40;i++)
    for(nombre z=1;z<=9;z++)
        resultat+=f[i][0][9][z];
    
    std::cout << "Solution: " << resultat << std::endl;
}
