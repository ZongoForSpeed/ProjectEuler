#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

void probleme075()
{
    Timer t("probleme 75");
    // It turns out that 12 cm is the smallest length of wire that can be bent to form an integer 
    // sided right angle triangle in exactly one way, but there are many more examples.
    //
    //      12 cm: (3,4,5)
    //      24 cm: (6,8,10)
    //      30 cm: (5,12,13)
    //      36 cm: (9,12,15)
    //      40 cm: (8,15,17)
    //      48 cm: (12,16,20)
    //
    // In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right 
    // angle triangle, and other lengths allow more than one solution to be found; for example, using
    // 120 cm it is possible to form exactly three different integer sided right angle triangles.
    //
    //      120 cm: (30,40,50), (20,48,52), (24,45,51)
    //
    // Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one 
    // integer sided right angle triangle be formed?
    std::map<nombre, std::set<std::tuple<nombre, nombre, nombre>>> solutions;
    
    // const nombre limite = 150;
    const nombre limite = 1500000;
    const nombre max_p = std::sqrt(limite / 2) + 1;
    for (nombre p = 1; p < max_p; ++p)
    {
        for (nombre q = 1; q < p; ++q)
        {
            if ((p+q)%2 == 1 && arithmetiques::PGCD(p, q) == 1)
            {
                nombre a = p*p - q*q;
                nombre b = 2*p*q;
                if (a > b)
                    std::swap(a, b);
                nombre c = p*p + q*q;
                nombre l = a+b+c;
                for (nombre k = 1; k*l <= limite; ++k)
                {
                    solutions[k*l].insert(std::make_tuple(k*a, k*b, k*c));
                }
            }
        }
    }
    
    nombre resultat = 0;
    for (const auto & s: solutions)
    {
        if (s.second.size() == 1)
            ++resultat;
    }

    std::cout << "Solution: " << resultat << std::endl;
}