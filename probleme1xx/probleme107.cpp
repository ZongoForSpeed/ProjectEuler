#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"
#include "graphe.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;
typedef std::map<nombre, std::vector<paire>> graphe;

ENREGISTRER_PROBLEME(107, "Minimal network")
{
    // The following undirected network consists of seven vertices and twelve edges with a total 
    // weight of 243.
    //
    //
    //The same network can be represented by the matrix below.
    //
    //      	A	B	C	D	E	F	G
    //      A	-	16	12	21	-	-	-
    //      B	16	-	-	17	20	-	-
    //      C	12	-	-	28	-	31	-
    //      D	21	17	28	-	18	19	23
    //      E	-	20	-	18	-	-	11
    //      F	-	-	31	19	-	-	27
    //      G	-	-	-	23	11	27	-
    //
    // However, it is possible to optimise the network by removing some edges and still ensure that 
    // all points on the network remain connected. The network which achieves the maximum saving is 
    // shown below. It has a weight of 93, representing a saving of 243 − 93 = 150 from the original
    // network.
    //
    // Using network.txt (right click and 'Save Link/Target As...'), a 6K text file containing a network
    // with forty vertices, and given in matrix form, find the maximum saving which can be achieved by 
    // removing redundant edges whilst ensuring that the network remains connected.
	
	std::ifstream ifs("data/p107_network.txt");
    // std::ifstream ifs("data/p107_example.txt");

    Kruskal::aretes A;
    nombre i = 0;
    std::string ligne;
    while (ifs >> ligne)
    {
        std::vector<std::string> strings;
        boost::split(strings,ligne,boost::is_any_of(","));
        
        nombre j = 0;
        for (auto s: strings) 
        {
            if (s != "-" && i < j) 
                A.push_back(std::make_tuple(i, j, stoull(s)));
            ++j;
        }
        ++i;
    }
    
    Kruskal kruskal(A);
    Kruskal::aretes arbre_mini = kruskal.algorithme();
    
    auto somme_poids = [] (const nombre r, const Kruskal::arete & a) { return r + std::get<2>(a); };
    
    nombre resultat = std::accumulate(A.begin(), A.end(), 0UL, somme_poids) - std::accumulate(arbre_mini.begin(), arbre_mini.end(), 0UL, somme_poids);;
    // std::cout << A << std::endl;
	std::cout << "Solution: " << resultat << std::endl;
}
