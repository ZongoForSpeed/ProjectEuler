#include "problemes.h"
#include "arithmetiques.h"

#include <iostream>
#include <algorithm>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(39, "Integer right triangles")
{
    // If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
    //
    // {20,48,52}, {24,45,51}, {30,40,50}
    //
    // For which value of p ≤ 1000, is the number of solutions maximised?
    std::vector<nombre> solutions(1001, 0);
    for (nombre c = 1; 2*c < 1000; ++c)
    for (nombre b = 1; b < c; ++b)
    for (nombre a = 1; a < b; ++a)
    {
        if (a*a + b*b == c*c)
            solutions[a+b+c]++;
    }

    auto it = std::max_element(solutions.begin(),solutions.end());
    return std::to_string(std::distance(solutions.begin(), it));
}
