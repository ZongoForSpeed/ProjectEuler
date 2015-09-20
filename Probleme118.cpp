#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    std::set<vecteur> test(const std::set<nombre> & premiers, 
                           vecteur::const_iterator debut, 
                           vecteur::const_iterator fin)
    {
        std::set<vecteur> resultat;
        nombre p = arithmetiques::conversion_nombre<nombre>(debut, fin);
        if (premiers.find(p) != premiers.end())
            resultat.insert(vecteur(1,p));
        
        for (auto it = std::next(debut); it != fin; ++it)
        {
            nombre p = arithmetiques::conversion_nombre<nombre>(debut, it);
            if (premiers.find(p) != premiers.end())
            {
                std::set<vecteur> s = test(premiers, it, fin);
                if (!s.empty())
                {
                    for (vecteur v: s)
                    {
                        v.push_back(p);
                        std::sort(v.begin(), v.end());
                        resultat.insert(v);
                    }
                }
            }
        }
        
        return resultat;
    }
}

void probleme118()
{
    Timer t("probleme 118");
    // Using all of the digits 1 through 9 and concatenating them freely to form decimal integers, 
    // different sets can be formed. Interestingly with the set {2,5,47,89,631}, all of the elements 
    // belonging to it are prime.
    //
    // How many distinct sets containing each of the digits one through nine exactly once contain 
    // only prime elements?
    std::set<nombre> premiers;
    {
        Timer t("crible");
        premiers::crible23<nombre>(1000000000, std::inserter(premiers, premiers.begin()));
    }
    
    std::set<vecteur> resultat;
    
    std::vector<nombre> chiffres { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    do
    {
        auto s = test(premiers, chiffres.begin(), chiffres.end());
        resultat.insert(s.begin(), s.end());
    }
    while (std::next_permutation(chiffres.begin(), chiffres.end()));
    
    std::cout << "Solution: " << resultat.size() << std::endl;
}
