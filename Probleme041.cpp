#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;

void probleme041()
{
    Timer t("probleme 41");
    // We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once.
    // For example, 2143 is a 4-digit pandigital and is also prime.
    //
    // What is the largest n-digit pandigital prime that exists?
    std::deque<nombre> premiers;
    premiers::crible<nombre>(100000000, std::back_inserter(premiers));
    nombre resultat = 0;
    std::vector<nombre> pandigital {1,2,3,4,5,6,7,8,9};
    for (nombre p: premiers)
    {
        auto chiffres = chiffres::extraire_chiffres(p);
        if (std::is_permutation(pandigital.begin(), pandigital.begin() + chiffres.size(), chiffres.begin()))
            resultat = p;
    }
    std::cout << "Solution: " << resultat << std::endl;
}
