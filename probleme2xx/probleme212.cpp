#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/optional.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::pair<nombre, nombre> segment;
typedef std::tuple<nombre, nombre, nombre, nombre, nombre, nombre> cuboide;

namespace
{
    boost::optional<segment> intersection(nombre xA, nombre dxA, nombre xB, nombre dxB)
    {
        nombre x = std::max(xA, xB);
        nombre y = std::min(xA + dxA, xB + dxB);
        
        if (x < y)
            return segment(x, y - x);
        else
            return boost::none;
    }
    
    boost::optional<cuboide> intersection(const cuboide & A, const cuboide & B)
    {
        nombre xa, ya, za, dxa, dya, dza;
        nombre xb, yb, zb, dxb, dyb, dzb;
        std::tie(xa, ya, za, dxa, dya, dza) = A;
        std::tie(xb, yb, zb, dxb, dyb, dzb) = B;
        
        if (auto x = intersection(xa, dxa, xb, dxb))
        if (auto y = intersection(ya, dya, yb, dyb))
        if (auto z = intersection(za, dza, zb, dzb))
        {
            return cuboide(x->first, y->first, z->first, x->second, y->second, z->second);
        }
        
        return boost::none;
    }
    
    nombre volume(const cuboide & A)
    {
        nombre dx, dy, dz;
        std::tie(std::ignore, std::ignore, std::ignore, dx, dy, dz) = A;
        return dx*dy*dz;
    }
}

ENREGISTRER_PROBLEME(212, "Combined Volume of Cuboids")
{
    // An axis-aligned cuboid, specified by parameters { (x0,y0,z0), (dx,dy,dz) }, consists of all 
    // points (X,Y,Z) such that x0 ≤ X ≤ x0+dx, y0 ≤ Y ≤ y0+dy and z0 ≤ Z ≤ z0+dz. The volume of 
    // the cuboid is the product, dx × dy × dz. The combined volume of a collection of cuboids is 
    // the volume of their union and will be less than the sum of the individual volumes if any cuboids
    // overlap.
    //
    // Let C1,...,C50000 be a collection of 50000 axis-aligned cuboids such that Cn has parameters
    // 
    // x0 = S6n-5 modulo 10000
    // y0 = S6n-4 modulo 10000
    // z0 = S6n-3 modulo 10000
    // dx = 1 + (S6n-2 modulo 399)
    // dy = 1 + (S6n-1 modulo 399)
    // dz = 1 + (S6n modulo 399)
    // 
    // where S1,...,S300000 come from the "Lagged Fibonacci Generator":
    //
    // For 1 ≤ k ≤ 55, Sk = [100003 - 200003k + 300007k3]   (modulo 1000000)
    // For 56 ≤ k, Sk = [Sk-24 + Sk-55]   (modulo 1000000)
    //
    // Thus, C1 has parameters {(7,53,183),(94,369,56)}, C2 has parameters {(2383,3563,5079),(42,212,344)},
    // and so on.
    //
    // The combined volume of the first 100 cuboids, C1,...,C100, is 723581599.
    // 
    // What is the combined volume of all 50000 cuboids, C1,...,C50000 ?
    nombre limite = 50000;
	vecteur s(6*limite + 1, 0);
	for (nombre k = 1; k < 56; ++k)
	{
		s.at(k) = (300007*k*k*k - 200003*k + 100003)%1000000;
	}
	for (nombre k = 56; k < 6*limite + 1; ++k)
	{
		s.at(k) = (s.at(k-24) + s.at(k-55) + 1000000)%1000000;
	}
	
	std::vector<cuboide> cuboides;
	for (nombre n = 1; n <= limite; ++n)
	{
	    cuboide C = std::make_tuple(s[6*n-5]%10000, s[6*n-4]%10000, s[6*n-3]%10000, 
	                                1 + s[6*n-2]%399, 1 + s[6*n-1]%399, 1 + s[6*n]%399);
	    cuboides.push_back(C);
	}

	std::vector<std::pair<cuboide, bool>> I;
	for (auto c: cuboides)
	{
        std::vector<std::pair<cuboide, bool>> tmp { std::make_pair(c, true) };
        for (auto i: I)
        {
            if (auto p = intersection(i.first, c))
            {
                tmp.push_back(std::make_pair(*p, !i.second));
            }
        }
        
        I.insert(I.end(), tmp.begin(), tmp.end());
    }
    
    nombre resultat_plus = 0;
    nombre resultat_moins = 0;
    
    for (auto i: I)
    {
        if (i.second)
            resultat_plus += volume(i.first);
        else 
            resultat_moins += volume(i.first);
    }
	
	nombre resultat = resultat_plus - resultat_moins;
	
    return std::to_string(resultat);
}
