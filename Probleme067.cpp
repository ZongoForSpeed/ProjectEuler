#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <fstream>
#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

void probleme067()
{
    Timer t("probleme 67");
    // By starting at the top of the triangle below and moving to adjacent numbers on the row below, 
    // the maximum total from top to bottom is 23.
    //
    //                                             3
    //                                            7 4
    //                                           2 4 6
    //                                          8 5 9 3
    //
    // That is, 3 + 7 + 4 + 9 = 23.
    // 
    // Find the maximum total from top to bottom in triangle.txt (right click and 'Save Link/Target As...'), 
    // a 15K text file containing a triangle with one-hundred rows.
    //
    // NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route 
    // to solve this problem, as there are 299 altogether! If you could check one trillion (1012) routes 
    // every second it would take over twenty billion years to check them all. There is an efficient 
    // algorithm to solve it. ;o)
    std::ifstream ifs("data/p067_triangle.txt");
    matrice triangle;
    vecteur v;
    nombre n;
    while(ifs >> n)
    {
        v.push_back(n);
        if (v.size() > triangle.size())
        {
            triangle.push_back(v);
            v.clear();
        }
    }
    
    const size_t taille = triangle.size();
    matrice resultat;
    for (size_t i = 0; i < taille; ++i)
    {
        vecteur ligne;
        if (i == 0)
            ligne.push_back(triangle[i][i]);
        else for (size_t j = 0; j <= i; ++j)
        {
            if (j == 0)
                ligne.push_back(resultat[i-1][j] + triangle[i][j]);
            else if (i == j)
                ligne.push_back(resultat[i-1][j-1] + triangle[i][j]);
            else
                ligne.push_back(std::max(resultat[i-1][j-1],resultat[i-1][j]) + triangle[i][j]);
        }
        resultat.push_back(ligne);
    }
    const auto it = std::max_element(resultat.back().begin(), resultat.back().end());
    std::cout << "Solution: " << *it << std::endl;
}

