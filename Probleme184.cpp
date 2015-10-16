#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    struct Point
    {
        long double x;
        long double y;
        
        Point(long double _x, long double _y) : x(_x), y(_y) {}
        
        bool operator<(const Point & p) const
        {
            if (x != p.x)
                return x < p.x;
            return y < p.y;
        }
    };
    
    nombre aire(const Point & A, const Point & B, const Point & C)
    {
        return abs(A.x*C.y - A.x*B.y + B.x*A.y - B.x*C.y + C.x*B.y - C.x*A.y);
    }
    
    std::ostream& operator<<(std::ostream& os, const Point & p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

}

ENREGISTRER_PROBLEME(184)
{
    Timer timer("probleme 184");
    // Consider the set Ir of points (x,y) with integer co-ordinates in the interior of the circle 
    // with radius r, centered at the origin, i.e. x2 + y2 < r2.
    //
    // For a radius of 2, I2 contains the nine points (0,0), (1,0), (1,1), (0,1), (-1,1), (-1,0), 
    // (-1,-1), (0,-1) and (1,-1). There are eight triangles having all three vertices in I2 which 
    // contain the origin in the interior. Two of them are shown below, the others are obtained from 
    // these by rotation.
    //
    // For a radius of 3, there are 360 triangles containing the origin in the interior and having all 
    // vertices in I3 and for I5 the number is 10600.
    //
    // How many triangles are there containing the origin in the interior and having all three vertices 
    // in I105?
    nombre limite = 105;
    const Point origine (0,0);
    
    std::vector<std::pair<Point, nombre>> points;
    for (nombre x = 0; x < limite; ++x)
    for (nombre y = 1; y < limite; ++y)
    {
        nombre r2 = x*x + y*y;
        if (r2 > 0 && r2 < limite*limite && arithmetiques::PGCD(x, y) == 1)
            points.push_back(std::make_pair(Point(x,y), std::sqrt((limite*limite - 1) / r2)));
    }
    
    std::sort(points.begin(), points.end());

    nombre resultat = 0;
    size_t longueur = points.size();
    for (size_t i = 0; i < longueur; ++i)
    {
        nombre compteur = 0;
        for (size_t j = i + 1; j < i + 2*longueur; ++j)
        {
            resultat += points[i].second * points[j%longueur].second * compteur;
            compteur += points[j%longueur].second;
        }
    }

    std::cout << "Solution: " << resultat * 4 / 3 << std::endl;
}
