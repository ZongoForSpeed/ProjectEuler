#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool test(const std::vector<unsigned char> & cote1, const std::vector<unsigned char> & cote2)
    {
        if (cote1.size() != cote2.size())
            return false;
            
        for (size_t n = 0; n < cote1.size(); ++n)
        {
            if (cote1[n] == cote2[n])
                return false;
        }
        
        return true;
    }
}

ENREGISTRER_PROBLEME(189, "Tri-colouring a triangular grid")
{
    Timer timer("probleme 189");
    // Consider the following configuration of 64 triangles:
    //
    // We wish to colour the interior of each triangle with one of three colours: red, green or blue,
    // so that no two neighbouring triangles have the same colour. Such a colouring shall be called 
    // valid. Here, two triangles are said to be neighbouring if they share an edge.
    // Note: if they only share a vertex, then they are not neighbours.
    //
    // For example, here is a valid colouring of the above grid:
    //
    // A colouring C' which is obtained from a colouring C by rotation or reflection is considered 
    // distinct from C unless the two are identical.
    //
    // How many distinct valid colourings are there for the above configuration?
    typedef unsigned char couleur;
    std::vector<couleur> couleurs { 'R', 'V', 'B' };
    
    std::vector<std::vector<couleur>> triangles4;
    std::map<std::vector<couleur>, nombre> cotes;
    
    for (auto a1: couleurs) 
    for (auto a2: couleurs) 
    for (auto a3: couleurs) 
    for (auto a4: couleurs)
    for (auto b1: couleurs) if (b1 != a1 && b1 != a2)
    for (auto b2: couleurs) if (b2 != a2 && b2 != a3)
    for (auto b3: couleurs) if (b3 != a3 && b3 != a4)
    for (auto c1: couleurs) if (b1 != c1)
    for (auto c2: couleurs) if (b2 != c2)
    for (auto c3: couleurs) if (b3 != c3)
    for (auto d1: couleurs) if (d1 != c1 && d1 != c2)
    for (auto d2: couleurs) if (d2 != c2 && d2 != c3)
    for (auto e1: couleurs) if (d1 != e1)
    for (auto e2: couleurs) if (d2 != e2)
    for (auto f1: couleurs) if (f1 != e1 && f1 != e2)
    for (auto g1: couleurs) if (g1 != f1)
    {
        std::vector<couleur> cote { a1, a2, a3, a4 };
        cotes[cote]++;
        std::vector<couleur> triangle { a1, a2, a3, a4, c3, e2, g1, e1, c1, a1 };
        triangles4.push_back(triangle);
    }
    
    nombre resultat = 0;
    for (auto t: triangles4)
    {
        std::vector<couleur> cote1(t.begin(), t.begin() + 4);
        std::vector<couleur> cote2(t.begin() + 3, t.begin() + 7);
        std::vector<couleur> cote3(t.begin() + 6, t.begin() + 10);

        nombre valeur1 = 0;
        nombre valeur2 = 0;
        nombre valeur3 = 0;
        for (auto p: cotes)
        {
            if (test(cote1, p.first)) valeur1 += p.second;
            if (test(cote2, p.first)) valeur2 += p.second;
            if (test(cote3, p.first)) valeur3 += p.second;
        }
        resultat += valeur1 * valeur2 * valeur3;
    }

    std::cout << "Solution: " << resultat << std::endl;
}
