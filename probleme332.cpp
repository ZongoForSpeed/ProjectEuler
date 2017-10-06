#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "premiers.h"
#include "puissance.h"
#include "arithmetiques.h"
#include "multidimension.h"

#include <cmath>

typedef long double nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> point;

namespace 
{
    nombre distance(nombre a, nombre b) {
        return std::sqrt(a*a + b*b);
    }
    
    // nombre distance(nombre a, nombre b, nombre c) {
    //     return std::sqrt(a*a + b*b + c*c);
    // }
    
    paire coordonnees_polaire(nombre a, nombre b, nombre c) {
        nombre lambda = std::atan2(a, b);
        nombre d = distance(a, b);
        nombre phi = std::atan2(d, c);
        
        return std::make_pair(phi, lambda);
    }
    
    paire coordonnees_polaire(const point & p) {
        nombre a,b,c;
        std::tie(a,b,c) = p;
        return coordonnees_polaire(a,b,c);
    }
    
    nombre angle(const paire & p1, const paire & p2) {
        nombre phi1 = p1.first;
        nombre phi2 = p2.first;
        
        nombre lambda1 = p1.second;
        nombre lambda2 = p2.second;
        
        return std::acos(std::sin(phi1)*std::sin(phi2) + std::cos(phi1)*std::cos(phi2)*std::cos(lambda2 - lambda1));
    }
    
    nombre angle_solide(const paire & p1, const paire & p2, const paire & p3) {
        nombre a = std::abs(angle(p1, p2));
        nombre b = std::abs(angle(p2, p3));
        nombre c = std::abs(angle(p3, p1));
        nombre s = (a + b + c) / 2;
        
        nombre e = std::tan(s / 2) * std::tan((s - a) / 2) * std::tan((s - b) / 2) * std::tan((s - b) / 2);
        return 4 * std::atan(std::sqrt(e));
    }
}

ENREGISTRER_PROBLEME(332, "Spherical triangles")
{
    // A spherical triangle is a figure formed on the surface of a sphere by three great circular arcs 
    // intersecting pairwise in three vertices.
    //
    // p332_spherical.jpg
    // Let C(r) be the sphere with the centre (0,0,0) and radius r.
    // Let Z(r) be the set of points on the surface of C(r) with integer coordinates.
    // Let T(r) be the set of spherical triangles with vertices in Z(r). Degenerate spherical triangles, 
    // formed by three points on the same great arc, are not included in T(r).
    // Let A(r) be the area of the smallest spherical triangle in T(r).
    //
    // For example A(14) is 3.294040 rounded to six decimal places.
    //
    // Find p332_sum.gif A(r). Give your answer rounded to six decimal places.
    nombre resultat = 0.0;
    
    std::vector<point> points;
    
    for (int a = 0; a < 15; ++a)
    for (int b = 0; b < 15; ++b)
    for (int c = 0; c < 15; ++c) {
        if (auto r = carre_parfait(a*a + b*b + c*c)) {
            if (*r == 14) {
                points.push_back(std::make_tuple(a,b,c));
                // points.push_back(std::make_tuple(-a,b,c));
                // points.push_back(std::make_tuple(a,-b,c));
                // points.push_back(std::make_tuple(a,b,-c));
                // // points.push_back(std::make_tuple(a,b,c));
            }    
        }
    }
    
    std::cout << points << std::endl;
    
    for (auto it1 = points.begin(), en = points.end(); it1 != en; ++it1) {
        auto p1 = coordonnees_polaire(*it1);
        for (auto it2 = std::next(it1); it2 != en; ++it2) {
            auto p2 = coordonnees_polaire(*it2);
            for (auto it3 = std::next(it1); it3 != en; ++it3) {
                auto p3 = coordonnees_polaire(*it3);
                nombre aire = 14*14*angle_solide(p1, p2, p3);
                if (aire > 0) {
                    std::cout << std::make_tuple(*it1, *it2, *it3) << " = " << aire << std::endl;
                }
            }
        }
    }
    
    return std::to_string(resultat);
}
