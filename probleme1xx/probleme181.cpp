#include "problemes.h"
#include "arithmetiques.h"
#include "multidimension.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>
#include <boost/multiprecision/gmp.hpp>

typedef unsigned long long nombre;

typedef std::vector<nombre> vecteur;
typedef multidimension<nombre, 2> matrice;
typedef std::pair<nombre, nombre> paire;
typedef boost::rational<nombre> fraction;

namespace
{
    bool incrementer(const paire & objets, paire & index, const paire & headRoom) 
    {
        if (index.first + headRoom.first < objets.first)
        {
            index.first++;
            return true;
        }
        index.first = 0;
        
        if (index.second + headRoom.second < objets.second)
        {
            index.second++;
            return true;
        }
        index.second = 0;
		return false;
	}
}

ENREGISTRER_PROBLEME(181, "Investigating in how many ways objects of two different colours can be grouped")
{
    // Having three black objects B and one white object W they can be grouped in 7 ways like this:
    //
    //      (BBBW)   (B,BBW)   (B,B,BW)   (B,B,B,W)   (B,BB,W)   (BBB,W)   (BB,BW)
    //
    // In how many ways can sixty black objects B and forty white objects W be thus grouped?
    paire objets(60, 40);
    
    matrice combinaison(objets.first + 1, objets.second + 1, 0UL);
    combinaison[0][0] = 1;
    
    paire zero(0, 0);
    paire addition(0, 0);
    
    while (incrementer(objets, addition, zero))
    {
        paire debut(0, 0);
        do
        {
            combinaison[debut.first + addition.first][debut.second + addition.second] 
                += combinaison[debut.first][debut.second];
        }
        while (incrementer(objets, debut, addition));
    }
    
    nombre resultat = combinaison[objets.first][objets.second];
    std::cout << "Solution: " << resultat << std::endl;
}
