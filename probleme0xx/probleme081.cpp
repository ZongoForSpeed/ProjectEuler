#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(81, "Path sum: two ways")
{
    Timer t("probleme 81");
    // In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by 
    // only moving to the right and down, is indicated in bold red and is equal to 2427.
    //		      
    //              131 673 234 103  18
    //              201  96 342 965 150
    //              630 803 746 422 111
    //              537 699 497 121 956
    //              805 732 524  37 331
    //
    // Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K
    // text file containing a 80 by 80 matrix, from the top left to the bottom right by only moving 
    // right and down.
    matrice graphe;
    std::ifstream ifs("data/p081_matrix.txt");
    std::string ligne;
    while (ifs >> ligne)
    {
        std::vector<std::string> v;
        boost::split(v,ligne,boost::is_any_of(","));
        vecteur l;
        for (const auto & s: v)
        {
            l.push_back(std::stoull(s));
        }
        graphe.push_back(l);
    }
    
    const nombre taille = graphe.size();
    matrice chemin(taille, vecteur(taille, 0));
    for (size_t i = 0; i < taille; ++i)
    for (size_t j = 0; j < taille; ++j)
    {
        if (i == 0 && j == 0)
            chemin[i][j] = graphe[i][j];
        else if (i == 0) 
            chemin[i][j] = graphe[i][j] + chemin[i][j - 1];
        else if (j == 0) 
            chemin[i][j] = graphe[i][j] + chemin[i - 1][j];
        else 
            chemin[i][j] = graphe[i][j] + std::min(chemin[i][j - 1], chemin[i - 1][j]);

    }
    std::cout << "Solution: " << chemin.back().back() << std::endl;
}
