#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme072()
{
    Timer t("probleme 72");
    // Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
    //
    // If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
    //
    // 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
    // 
    // It can be seen that there are 21 elements in this set.
    //
    // How many elements would be contained in the set of reduced proper fractions for d ≤ 1,000,000?
    nombre limite = 1000000;
    vecteur premiers;
    premiers::crible23<nombre>(limite, std::back_inserter(premiers));
    
    nombre resultat = 0;
    for (nombre n = 2; n <= limite; ++n)
    {
        resultat += arithmetiques::phi(n, premiers);   
    }
    std::cout << "Solution: " << resultat << std::endl;
}