#include "Problemes.h"
#include "Premiers.h"
#include "Chiffres.h"
#include "Timer.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(51, "Prime digit replacements")
{
    Timer t("probleme 51");
    // By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine 
    // possible values: 13, 23, 43, 53, 73, and 83, are all prime.
    // 
    // By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number 
    // is the first example having seven primes among the ten generated numbers, yielding the 
    // family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being 
    // the first member of this family, is the smallest prime with this property.
    //
    // Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) 
    // with the same digit, is part of an eight prime value family.
    nombre limite = 1000000;
    
    std::set<nombre> premiers;
    premiers::crible<nombre>(limite, std::inserter(premiers, premiers.begin()));
    
    nombre resultat = 0;
    nombre trouve = false;
    for (auto it1 = premiers.begin(), en = premiers.end(); it1 != en; ++it1)
    {
        nombre p = *it1;
        auto chiffres = chiffres::extraire_chiffres(p);
        std::set<nombre> chiffres_uniques(chiffres.begin(), chiffres.end());
        for (const auto c: chiffres_uniques)
        {
            if (c != 0)
            {
                auto chiffres2 = chiffres;
                std::replace(chiffres2.begin(), chiffres2.end(), c, nombre(0));
                nombre q = chiffres::conversion_nombre<nombre>(chiffres2.begin(), chiffres2.end());
                nombre difference = (p - q)/c;
                nombre compteur = 0;
                for (nombre n = c; n < 10; ++n)
                {
                    if (premiers.find(q + n*difference) != premiers.end()) ++compteur;
                }
                
                if (compteur == 8)
                {
                    resultat = p;
                    trouve = true;
                    break;
                }
            }
        }
        if (trouve)
            break;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
