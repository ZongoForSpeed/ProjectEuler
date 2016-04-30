#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(77, "Prime summations")
{
    // It is possible to write ten as the sum of primes in exactly five different ways:
    //
    //      7 + 3
    //      5 + 5
    //      5 + 3 + 2
    //      3 + 3 + 2 + 2
    //      2 + 2 + 2 + 2 + 2
    //
    // What is the first value which can be written as the sum of primes in over five thousand 
    // different ways?
    std::set<nombre> premiers;
    premiers::crible23<nombre>(1000000, std::inserter(premiers, premiers.begin()));
    nombre n = 4;
    std::map<nombre, std::set<vecteur>> solutions;
    while (true)
    {
        std::set<vecteur> solutions_n;
        for (const auto p: premiers)
        {
            if (p >= n)
                break;
            
            if (premiers.find(n - p) != premiers.end())
            {
                vecteur s = { n-p, p };
                std::sort(s.begin(), s.end());
                solutions_n.insert(s);
            }
            
            auto it = solutions.find(n-p);
            if (it != solutions.end())
            {
                for (auto s: it->second)
                {
                    s.push_back(p);
                    std::sort(s.begin(), s.end());
                    solutions_n.insert(s);
                }
            }
        }
        solutions[n] = solutions_n;
        if (solutions_n.size() > 5000)
            break;
        ++n;
    }
    
    std::cout << "Solution: " << n << std::endl;
}
