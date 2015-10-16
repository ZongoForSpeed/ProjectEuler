#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"
#include "Graphe.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

typedef std::pair<nombre, nombre> paire;
typedef std::vector<paire> vecteur_paire;

ENREGISTRER_PROBLEME(83)
{
    Timer t("probleme 83");
    // In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, 
    // by moving left, right, up, and down, is indicated in bold red and is equal to 2297.
    //
    // Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K 
    // text file containing a 80 by 80 matrix, from the top left to the bottom right by moving left, 
    // right, up, and down.
    matrice m;
    std::ifstream ifs("data/p083_matrix.txt");
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
        m.push_back(l);
    }
    
    const nombre taille = m.size();
    Dijkstra::graphe graphe;
    for (nombre i = 0; i < taille; ++i)
    for (nombre j = 0; j < taille; ++j)
    {
        vecteur_paire v;
        const nombre poids = m[i][j]; 
        if (i > 0)            
            v.push_back(std::make_pair((i-1) * taille + j, poids));
        if (j > 0) 
            v.push_back(std::make_pair(i * taille + j - 1, poids));
        if (i < taille - 1)   
            v.push_back(std::make_pair((i + 1) * taille + j, poids));
        if (j < taille - 1) 
            v.push_back(std::make_pair(i * taille + j + 1, poids));
            
        graphe[i*taille + j] = v;
    }
    
    Dijkstra dijkstra(graphe, 0, (taille - 1) * (taille + 1));
    nombre resultat = dijkstra.algorithme() + m[taille - 1][taille - 1];
    std::cout << "Solution: " << resultat << std::endl;
}
