#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"

#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(26, "Reciprocal cycles")
{
    Timer t("probleme 26");
    // A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions 
    // with denominators 2 to 10 are given:
    //
    //    1/2    =     0.5
    //    1/3    =     0.(3)
    //    1/4    =     0.25
    //    1/5    =     0.2
    //    1/6    =     0.1(6)
    //    1/7    =     0.(142857)
    //    1/8    =     0.125
    //    1/9    =     0.(1)
    //    1/10    =     0.1
    // 
    // Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 
    // has a 6-digit recurring cycle.
    // 
    // Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
    auto longueur_cycle = [](nombre n) -> nombre
    {
        vecteur restes;
        nombre reste = 1;
        while (std::find(restes.begin(), restes.end(), reste) == restes.end())
        {
            restes.push_back(reste);
            while (reste%n == reste) reste *= 10;
            reste = reste%n;
        }
        return restes.size();
    };
    
    nombre l_max = 0;
    nombre resultat = 0;
    for (nombre n = 3; n < 1000; ++n)
    {
        if (n%2 != 0 && n%5 != 0)
        {
            nombre l = longueur_cycle(n);
            if (l > l_max)
            {
                l_max = l;
                resultat = n;
            }
        }
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
