#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

// typedef unsigned long long nombre;

typedef boost::multiprecision::mpz_int nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> paire;

namespace
{
    nombre combinaison_b(nombre couleur)
    {
        nombre c = couleur - 2;
        nombre resultat = 0;
        
        resultat += c*c*c + c;
        resultat += c*(c*c*c + c*c + c - 1);
        resultat += (c - 1)*c*(c*c*c + c - 2);
        resultat += 2*c * (c*c*c + c - 1);
        
        return resultat;
    }
    
    nombre combinaison_a(nombre couleur)
    {
        nombre c = couleur - 2;
        nombre resultat = 0;
        
        resultat += 1 * (c*c*c + c);
        resultat += (c-1)*c * (c*c*c + c - 2);
        resultat += (2*c) * (c*c*c + c - 1);
        
        return resultat;
    }
    
    nombre N(nombre a, nombre b, nombre c)
    {
        if (a == 0 && b == 0)
            return c*(c - 1);
        
        static std::map<std::tuple<nombre, nombre, nombre>, nombre> cache;
        auto it = cache.find(std::make_tuple(a, b, c));
        if (it != cache.end())
            return it->second;
            
        nombre resultat = 0;
        if (b > 0)
            resultat += combinaison_b(c)*N(a, b - 1, c);
            
        if (a > 0)
            resultat += combinaison_a(c)*N(a - 1, b, c);
            
        cache[std::make_tuple(a, b, c)] = resultat;
        return resultat;
    }
}

ENREGISTRER_PROBLEME(194, "Coloured Configurations")
{
    Timer timer("probleme 194");
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
    std::cout << "N(1,0,3) = " << N(1, 0, 3) << std::endl;
    std::cout << "N(0,2,4) = " << N(0, 2, 4) << std::endl;
    std::cout << "N(2,2,3) = " << N(2, 2, 3) << std::endl;

    nombre resultat = N(25,75,1984) % 100000000;
    std::cout << "N(25,75,1984) = " << resultat << std::endl;
    
    std::cout << "Solution: " << resultat << std::endl;
}
