#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;

ENREGISTRER_PROBLEME(91, "Right triangles with integer coordinates")
{
    Timer t("probleme 91");
    // The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates and are joined to 
    // the origin, O(0,0), to form ΔOPQ.
    //
    // There are exactly fourteen triangles containing a right angle that can be formed when each 
    // co-ordinate lies between 0 and 2 inclusive; that is, 0 ≤ x1, y1, x2, y2 ≤ 2.
    //
    // Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?
    const nombre limite = 50;
    std::vector<paire> points;
    for (nombre i = 0; i <= limite; ++i)
    for (nombre j = 0; j <= limite; ++j)
        if (i != 0 || j != 0) points.push_back(std::make_pair(i,j));
    
    auto triangle_rectangle = [] (const paire & p1, const paire & p2) -> bool
    {
        paire p12 = std::make_pair(p1.first - p2.first, p1.second - p2.second);
        return ((p12.first * p1.first + p12.second * p1.second == 0)
            || (p12.first * p2.first + p12.second * p2.second == 0)
            || (p1.first * p2.first + p1.second * p2.second == 0));
    };
    
    nombre resultat = 0;
    for (auto it1 = points.begin(), en = points.end(); it1 != en; ++it1)
    for (auto it2 = it1 + 1; it2 != en; ++it2)
    {
        if (triangle_rectangle(*it1, *it2))
            ++resultat;
    }
    std::cout << "Solution: " << resultat << std::endl;
}
