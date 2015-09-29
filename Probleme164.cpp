#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

// typedef boost::multiprecision::mpz_int nombre;

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;
typedef std::vector<matrice> cache;

namespace
{
    nombre compte(cache & compteur, nombre d1, nombre d2, nombre reste) 
	{
        if (reste == 0)
            return 1;
        else if (compteur[d1][d2][reste] == 0)
                for (nombre i=0; i< 10 - (d1+d2); i++)
                    compteur[d1][d2][reste] += compte(compteur, d2, i, reste-1);
        return compteur[d1][d2][reste];
    }
}

void probleme164()
{
    Timer timer("probleme 164");
    // How many 20 digit numbers n (without any leading zero) exist such that no three consecutive
    // digits of n have a sum greater than 9?
    const nombre limite = 20;
    cache compteur(10, matrice(10, vecteur(limite,0)));
    
    nombre resultat = 0;
    for (nombre i = 1; i < 10; ++i)
    {
    	resultat += compte(compteur, 0, i, limite - 1);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
