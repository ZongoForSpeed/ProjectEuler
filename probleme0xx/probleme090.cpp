#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(90, "Cube digit pairs")
{
    // Each of the six faces on a cube has a different digit (0 to 9) written on it; the same is 
    // done to a second cube. By placing the two cubes side-by-side in different positions we can
    // form a variety of 2-digit numbers.
    //
    // For example, the square number 64 could be formed:
    //
    // In fact, by carefully choosing the digits on both cubes it is possible to display all of the
    // square numbers below one-hundred: 01, 04, 09, 16, 25, 36, 49, 64, and 81.
    // 
    // For example, one way this can be achieved is by placing {0, 5, 6, 7, 8, 9} on one cube and 
    // {1, 2, 3, 4, 8, 9} on the other cube.
    // 
    // However, for this problem we shall allow the 6 or 9 to be turned upside-down so that an 
    // arrangement like {0, 5, 6, 7, 8, 9} and {1, 2, 3, 4, 6, 7} allows for all nine square numbers 
    // to be displayed; otherwise it would be impossible to obtain 09.
    // 
    // In determining a distinct arrangement we are interested in the digits on each cube, not the order.
    // 
    //      {1, 2, 3, 4, 5, 6} is equivalent to {3, 6, 4, 1, 2, 5}
    //      {1, 2, 3, 4, 5, 6} is distinct from {1, 2, 3, 4, 5, 9}
    //
    // But because we are allowing 6 and 9 to be reversed, the two distinct sets in the last example 
    // both represent the extended set {1, 2, 3, 4, 5, 6, 9} for the purpose of forming 2-digit numbers.
    // 
    // How many distinct arrangements of the two cubes allow for all of the square numbers to be displayed?
    std::set<vecteur> des;
    vecteur de = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    do
    {
        vecteur v(de.begin(), de.begin() + 6);
        std::sort(v.begin(), v.end());
        des.insert(v);
    }
    while(std::next_permutation(de.begin(), de.end()));
    
    auto test = [] (const vecteur & de1, const vecteur & de2, nombre c1, nombre c2)
    {
        return ((std::find(de1.begin(), de1.end(), c1) != de1.end() && std::find(de2.begin(), de2.end(), c2) != de2.end())
            || (std::find(de1.begin(), de1.end(), c2) != de1.end() && std::find(de2.begin(), de2.end(), c1) != de2.end()));
    };
    
    nombre resultat = 0;
    for (auto it1 = des.begin(), en = des.end(); it1 != en; ++it1)
    for (auto it2 = it1; it2 != en; ++it2)
    {
        // 01, 04, 09, 16, 25, 36, 49, 64, and 81
        if (!test(*it1, *it2, 0, 1)) 
            continue;
        if (!test(*it1, *it2, 0, 4)) 
            continue;
        if (!test(*it1, *it2, 0, 9) && !test(*it1, *it2, 0, 6)) 
            continue;
        if (!test(*it1, *it2, 1, 6) && !test(*it1, *it2, 1, 9)) 
            continue;
        if (!test(*it1, *it2, 2, 5)) 
            continue;
        if (!test(*it1, *it2, 3, 6) && !test(*it1, *it2, 3, 9)) 
            continue;
        if (!test(*it1, *it2, 4, 9) && !test(*it1, *it2, 4, 6)) 
            continue;
        if (!test(*it1, *it2, 6, 4) && !test(*it1, *it2, 9, 4)) 
            continue;
        if (!test(*it1, *it2, 8, 1)) 
            continue;

        ++resultat;
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
