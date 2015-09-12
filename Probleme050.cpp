#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme050()
{
    Timer t("probleme 50");
    // The prime 41, can be written as the sum of six consecutive primes:
    //                                      41 = 2 + 3 + 5 + 7 + 11 + 13
    //
    // This is the longest sum of consecutive primes that adds to a prime below one-hundred.
    // 
    // The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, 
    // and is equal to 953.
    // 
    // Which prime, below one-million, can be written as the sum of the most consecutive primes?
    nombre limite = 1000000;
    
    std::set<nombre> premiers;
    premiers::crible<nombre>(limite, std::inserter(premiers, premiers.begin()));
    
    nombre resultat = 0;
    nombre longueur = 0;
    for (auto it1 = premiers.begin(), en = premiers.end(); it1 != en; ++it1)
    {
        nombre s = *it1;
        nombre l = 1;
        for (auto it2 = std::next(it1,1); it2 != en; ++it2)
        {
            s += *it2;
            ++l;
            if (s > limite)
                break;
            if (premiers.find(s) != premiers.end() && l > longueur)
            {
                longueur = l;
                resultat = s;
            }
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}