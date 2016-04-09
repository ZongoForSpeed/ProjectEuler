#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/range/adaptor/reversed.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    const long double epsilon = 1e-9;

    struct comparedouble
    {
        bool operator () (const long double& lhs, const long double& rhs) const
        {
            if (std::abs(lhs - rhs) < epsilon)
                return false;
            else
                return lhs < rhs;
        }
    };
}

ENREGISTRER_PROBLEME(177, "Integer angled Quadrilaterals")
{
    Timer timer("probleme 177");
    // Let ABCD be a convex quadrilateral, with diagonals AC and BD. At each vertex the diagonal 
    // makes an angle with each of the two sides, creating eight corner angles.
    //
    // For example, at vertex A, the two angles are CAD, CAB.
    //
    // We call such a quadrilateral for which all eight corner angles have integer values when
    // measured in degrees an "integer angled quadrilateral". An example of an integer angled 
    // quadrilateral is a square, where all eight corner angles are 45°. Another example is given 
    // by DAC = 20°, BAC = 60°, ABD = 50°, CBD = 30°, BCA = 40°, DCA = 30°, CDB = 80°, ADB = 50°.
    //
    // What is the total number of non-similar integer angled quadrilaterals?
    //
    // Note: In your calculations you may assume that a calculated angle is integral if it is within
    // a tolerance of 10-9 of an integer value.
    std::vector<long double> sinus(180, 0.0);
    std::vector<long double> cosinus(180, 0.0);
    std::vector<long double> rad(180, 0.0);
    std::vector<bool> prevalue(10000 + 1, false);
    
    std::vector<nombre> solution(8+1, 0);
    
    std::set<long double, comparedouble> fs;
    for (nombre i = 1; i < 180; i++)
    {
        rad[i] = static_cast<long double>(i)*M_PI/180.0;
        sinus[i] = std::sin(rad[i]);
        cosinus[i] = std::cos(rad[i]);
        nombre j = static_cast<nombre>(sinus[i]*10000);
        prevalue[j] = true;
        fs.insert(sinus[i]);
    }
    prevalue[10000]= true; // sin90
    prevalue[10000-1]= true; // sin90
    prevalue[5000]= true; // sin30
    prevalue[5000-1]= true; //sin30

    for (nombre a = 1; a <= 45; a++)
    for (nombre b = a; a + b < 180 - 1; b++)
    for (nombre c = 1; a + b + c < 180; c++)
    {
        nombre d = 180 - a - b - c;
        for (nombre e = 1;e < b + d; e++)
        {
            nombre f = b + d - e;
            long double m = (sinus[b]*sinus[c]*sinus[f])/(sinus[a]*sinus[e]*sinus[d]);
            long double n = cosinus[a+c];
            long double siny = std::sqrt((1-n*n)/(m*m+2*m*n+1));
            nombre j = static_cast<nombre>(siny*10000);
            if(!prevalue[j]) continue;
            if (fs.find(siny) != fs.end())
            {
                if (siny > 1) siny=1;
                
                nombre y = static_cast<nombre>(std::asin(siny)*180/M_PI+0.01);
                long double sinx = m*siny;
                long double xangle = (std::abs(sinx-1) < epsilon) ? 90 : std::asin(sinx)*180/M_PI;
                nombre x = static_cast<nombre>(xangle+0.01);
                if (xangle < x + epsilon && xangle > x - epsilon)
                {
                    x = (180-x+y==a+c) ? 180 - x : x;
                    y = (180+x-y==a+c) ? 180 - y : y;
                    
                    std::vector<vecteur> quadrilateres
                    {
                        {a, b, d, y, x, f, e, c}, 
                        {d, y, x, f, e, c, a, b},
                        {x, f, e, c, a, b, d, y},
                        {e, c, a, b, d, y, x, f},
                        {b, a, c, e, f, x, y, d},
                        {c, e, f, x, y, d, b, a},
                        {f, x, y, d, b, a, c, e},
                        {y, d, b, a, c, e, f, x}
                    };
                    
                    std::set<vecteur> s;
                    for (auto quadrilatere: quadrilateres)
                    {
                        if (quadrilatere.front() <= quadrilatere.at(1) && quadrilatere.front() <= 45)
                            s.insert(quadrilatere);
                    }
                    
                    solution[s.size()]++;
                }
            }
        }
    }
    
    nombre resultat = 0;
    for(nombre i = 1; i <= 8; i++)
        resultat += solution[i] / i;
        
    std::cout << "Solution: " << resultat << std::endl;
}
