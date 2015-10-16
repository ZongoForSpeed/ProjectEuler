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
typedef std::set<nombre> ensemble;

ENREGISTRER_PROBLEME(127, "abc-hits")
{
    Timer t("probleme 127");
    // The radical of n, rad(n), is the product of distinct prime factors of n. For example, 
    // 504 = 23 × 32 × 7, so rad(504) = 2 × 3 × 7 = 42.
    //
    // We shall define the triplet of positive integers (a, b, c) to be an abc-hit if:
    //
    //      GCD(a, b) = GCD(a, c) = GCD(b, c) = 1
    //      a < b
    //      a + b = c
    //      rad(abc) < c
    //
    // For example, (5, 27, 32) is an abc-hit, because:
    //
    //      GCD(5, 27) = GCD(5, 32) = GCD(27, 32) = 1
    //      5 < 27
    //      5 + 27 = 32
    //      rad(4320) = 30 < 32
    //
    // It turns out that abc-hits are quite rare and there are only thirty-one abc-hits for c < 1000,
    // with ∑c = 12523.
    //
    // Find ∑c for c < 120000.
    nombre limite = 120000;
    ensemble premiers;
    premiers::crible23<nombre>(limite, std::inserter(premiers, premiers.begin()));
    
    vecteur radical { 0, 1 };
    for (nombre n = 2; n < limite; ++n)
        radical.push_back(arithmetiques::radical(n, premiers));
    
    nombre resultat = 0;
    for (nombre c = 3; c < limite; ++c)
    {
        if (premiers.find(c) != premiers.end())
            continue;
        nombre rad_c = radical[c];
        if (rad_c < c)
        {
            for (nombre a = 1; 2*a < c; ++a)
            {
                nombre b = c - a;
                nombre rad_a = radical[a];
                nombre rad_b = radical[b];
                if (rad_a * rad_b * rad_c < c && arithmetiques::PGCD(a, b) == 1)
                    resultat += c;
            }
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
