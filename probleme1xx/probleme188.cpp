#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    nombre cycle(nombre p, nombre m)
    {
        nombre n = p, i = 1;
        while (n != 1)
        {
            ++i;
            n = (n*p)%m;
        }
        return i;
    }
}

ENREGISTRER_PROBLEME(188, "The hyperexponentiation of a number")
{
    Timer timer("probleme 188");
    // The hyperexponentiation or tetration of a number a by a positive integer b, denoted by a↑↑b or ba, 
    // is recursively defined by:
    //
    // a↑↑1 = a,
    // a↑↑(k+1) = a(a↑↑k).
    //
    // Thus we have e.g. 3↑↑2 = 33 = 27, hence 3↑↑3 = 327 = 7625597484987 and 3↑↑4 is roughly 
    // 10^(3.6383346400240996*10^12).
    //
    // Find the last 8 digits of 1777↑↑1855.
    vecteur masques { 100000000 };
    while (masques.back() > 2)
        masques.push_back(cycle(1777, masques.back()));

    nombre resultat = 1;
    for (auto m : boost::adaptors::reverse(masques))
        resultat = puissance::puissance_modulaire<nombre>(1777, resultat, m);

    std::cout << "Solution: " << resultat << std::endl;
}
