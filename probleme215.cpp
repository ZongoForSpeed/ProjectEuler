#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool intersection(const std::set<nombre> & a, const std::set<nombre> & b)
    {
        std::set<nombre> i;
        std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(i, i.begin()));
        return i.empty();
    }
}

ENREGISTRER_PROBLEME(215, "Crack-free Walls")
{
    Timer timer("probleme 215");
    // Consider the problem of building a wall out of 2×1 and 3×1 bricks (horizontal×vertical dimensions)
    // such that, for extra strength, the gaps between horizontally-adjacent bricks never line up in 
    // consecutive layers, i.e. never form a "running crack".
    //
    // For example, the following 9×3 wall is not acceptable due to the running crack shown in red:
    //
    // There are eight ways of forming a crack-free 9×3 wall, written W(9,3) = 8.
    //
    // Calculate W(32,10).
    nombre taille = 32;
    nombre hauteur = 10;
    std::vector<std::set<nombre>> murs;
    for (nombre n = 0; 3*n <= taille; ++n)
    {
        if ((taille - 3*n)%2 == 0)
        {
            vecteur mur((taille - 3*n)/2, 2);
            mur.insert(mur.end(), n, 3);
            do 
            {
                std::set<nombre> set_mur;
                nombre l = 0;
                for (auto m: mur)
                {
                    set_mur.insert(l);
                    l += m;
                }
                set_mur.erase(set_mur.begin());
                murs.push_back(set_mur);
            }
            while(std::next_permutation(mur.begin(), mur.end()));
        }
    }
    
    std::map <std::set<nombre>, std::vector<std::set<nombre>>> I;
    for (auto m1: murs)
    for (auto m2: murs)
    {
        if (intersection(m1, m2))
            I[m1].push_back(m2);
    }

    std::map<std::set<nombre>, nombre> dp;
    for (auto m: I)
        dp[m.first] = m.second.size();

    for (nombre h = 2; h < hauteur; ++h)
    {
        std::map<std::set<nombre>, nombre> suite_dp;
        for (auto m: dp)
        {
            for (auto i: I[m.first])
                suite_dp[i] += m.second;
        }
        
        std::swap(suite_dp, dp);
    }

    nombre resultat = 0;
    for (auto m: dp)
        resultat += m.second;

    std::cout << "Solution: " << resultat << std::endl;
}
