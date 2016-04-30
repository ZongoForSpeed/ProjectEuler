#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(82, "Path sum: three ways")
{
    // The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column 
    // and finishing in any cell in the right column, and only moving up, down, and right, is 
    // indicated in red and bold; the sum is equal to 994.
    //
    // Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K 
    // text file containing a 80 by 80 matrix, from the left column to the right column.
    matrice graphe;
    std::ifstream ifs("data/p082_matrix.txt");
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
    {
		vecteur chemin_bas(taille, 0);
		for (size_t j = 0; j < taille; ++j)
		{
			if (i == 0)
				chemin_bas[j] = graphe[j][i];
			else if (j == 0)
				chemin_bas[j] = chemin[j][i-1] + graphe[j][i];
			else
				chemin_bas[j] = std::min(chemin[j][i-1],chemin_bas[j-1]) + graphe[j][i];
		}
		
		vecteur chemin_haut(taille, 0);
		for (size_t jj = 0; jj < taille; ++jj)
        {
            const size_t j = taille - jj - 1;
            if (i == 0)
				chemin_haut[j] = graphe[j][i];
			else if (j == taille - 1)
				chemin_haut[j] = chemin[j][i-1] + graphe[j][i];
			else
				chemin_haut[j] = std::min(chemin[j][i-1], chemin_haut[j+1]) + graphe[j][i];
        }
		
		for (size_t j = 0; j < taille; ++j)
			chemin[j][i] = std::min(chemin_haut[j], chemin_bas[j]);
    }
    
    nombre resultat = std::numeric_limits<nombre>::max();
    for (const auto & c: chemin)
    {
        resultat = std::min(resultat, c.back());
    }
    
    
    std::cout << "Solution: " << resultat << std::endl;
}
