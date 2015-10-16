#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

// #include <boost/multiprecision/gmp.hpp>
// #include <boost/rational.hpp>
// #include <boost/optional.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool pandigital(const nombre n, std::size_t base = 10)
    {
        std::vector<std::size_t> chiffres(base, 0);
        chiffres::boucle_chiffre(n, [&chiffres](nombre d){ chiffres[d]++; }, base);

        for (auto c: chiffres)
            if (c > 1) return false;
        return true;
    }
    
    bool pandigital_complet(const nombre n, std::size_t base = 10)
    {
        std::vector<std::size_t> chiffres(base, 0);
        chiffres::boucle_chiffre(n, [&chiffres](nombre d){ chiffres[d]++; }, base);

        for (auto c: chiffres)
            if (c != 1) return false;
        return true;
    }
}

ENREGISTRER_PROBLEME(170, "Find the largest 0 to 9 pandigital that can be formed by concatenating products")
{
    Timer timer("probleme 170");
    // Take the number 6 and multiply it by each of 1273 and 9854:
    //
    //          6 × 1273 = 7638
    //          6 × 9854 = 59124
    //
    // By concatenating these products we get the 1 to 9 pandigital 763859124. We will call 
    // 763859124 the "concatenated product of 6 and (1273,9854)". Notice too, that the concatenation
    // of the input numbers, 612739854, is also 1 to 9 pandigital.
    //
    // The same can be done for 0 to 9 pandigital numbers.
    //
    // What is the largest 0 to 9 pandigital 10-digit concatenated product of an integer with two or 
    // more other integers, such that the concatenation of the input numbers is also a 0 to 9 pandigital
    // 10-digit number?
    vecteur chiffres { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    nombre taille = chiffres.size();
    nombre resultat = 0;
    do 
    {
        if (chiffres.front() == 0)
            continue;
            
        for (size_t n0 = 1; n0 < taille - 1; ++n0)
        {
            if (chiffres[n0] == 0)
                continue;
            nombre facteur = chiffres::conversion_nombre<nombre>(chiffres.begin(), chiffres.begin() + n0);
            for (size_t n1 = n0 + 1; n1 < taille - 1; ++n1)
            {
                if (chiffres[n1] == 0)
                    continue;
                nombre a = chiffres::conversion_nombre<nombre>(chiffres.begin() + n0, chiffres.begin() + n1);
                if (a == 0 || !pandigital(facteur * a))
                    continue;
                
                nombre b = chiffres::conversion_nombre<nombre>(chiffres.begin() + n1, chiffres.end());
                if (b == 0 || !pandigital(facteur * b))
                    continue;
                
                nombre n = chiffres::concatener(facteur*a, facteur*b);
                if (pandigital_complet(n) && resultat < n)
                    resultat = std::max(resultat, n);
            }
        }
    } 
    while(std::next_permutation(chiffres.begin(), chiffres.end()));
    
    std::cout << "Solution: " << resultat << std::endl;
}
