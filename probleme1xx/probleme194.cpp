#include "problemes.h"
#include "arithmetiques.h"
#include "grand_nombre.h"

typedef std::vector<grand_nombre> vecteur;
typedef std::pair<grand_nombre, grand_nombre> paire;

namespace
{
    grand_nombre combinaison_b(grand_nombre couleur)
    {
        grand_nombre c = couleur - 2;
        grand_nombre resultat = 0;
        
        resultat += c*c*c + c;
        resultat += c*(c*c*c + c*c + c - 1);
        resultat += (c - 1)*c*(c*c*c + c - 2);
        resultat += 2*c * (c*c*c + c - 1);
        
        return resultat;
    }
    
    grand_nombre combinaison_a(grand_nombre couleur)
    {
        grand_nombre c = couleur - 2;
        grand_nombre resultat = 0;
        
        resultat += 1 * (c*c*c + c);
        resultat += (c-1)*c * (c*c*c + c - 2);
        resultat += (2*c) * (c*c*c + c - 1);
        
        return resultat;
    }
    
    grand_nombre N(std::map<std::tuple<grand_nombre, grand_nombre, grand_nombre>, grand_nombre> & cache, grand_nombre a, grand_nombre b, grand_nombre c)
    {
        if (a == 0 && b == 0)
            return c*(c - 1);
        
        auto it = cache.find(std::make_tuple(a, b, c));
        if (it != cache.end())
            return it->second;
            
        grand_nombre resultat = 0;
        if (b > 0)
            resultat += combinaison_b(c)*N(cache, a, b - 1, c);
            
        if (a > 0)
            resultat += combinaison_a(c)*N(cache, a - 1, b, c);
            
        cache[std::make_tuple(a, b, c)] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(194, "Coloured Configurations")
{
    // Consider graphs built with the units A:  and B: , where the units are glued along the vertical 
    // edges as in the graph .
    //
    // A configuration of type (a,b,c) is a graph thus built of a units A and b units B, where the 
    // graph's vertices are coloured using up to c colours, so that no two adjacent vertices have the 
    // same colour.
    // The compound graph above is an example of a configuration of type (2,2,6), in fact of type (2,2,c)
    // for all c ≥ 4.
    //
    // Let N(a,b,c) be the number of configurations of type (a,b,c).
    // For example, N(1,0,3) = 24, N(0,2,4) = 92928 and N(2,2,3) = 20736.
    //
    // Find the last 8 digits of N(25,75,1984).
    std::map<std::tuple<grand_nombre, grand_nombre, grand_nombre>, grand_nombre> cache;

    std::cout << "N(1,0,3) = " << N(cache, 1, 0, 3) << std::endl;
    std::cout << "N(0,2,4) = " << N(cache, 0, 2, 4) << std::endl;
    std::cout << "N(2,2,3) = " << N(cache, 2, 2, 3) << std::endl;

    grand_nombre resultat = N(cache, 25, 75, 1984) % 100000000;
    std::cout << "N(25,75,1984) = " << resultat << std::endl;
    
    return resultat.to_string();
}
