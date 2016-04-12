#include "problemes.h"
#include "arithmetiques.h"
#include "polygonal.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>
#include <boost/multiprecision/gmp.hpp>

typedef unsigned long long nombre;
typedef boost::multiprecision::mpz_int grand_nombre;

typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;
typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(180, "Rational zeros of a function of three variables")
{
    Timer timer("probleme 180");
    // For any integer n, consider the three functions
    //
    // f1,n(x,y,z) = x^n+1 + y^n+1 − z^n+1
    // f2,n(x,y,z) = (xy + yz + zx)*(x^n-1 + y^n-1 − z^n-1)
    // f3,n(x,y,z) = xyz*(x^n-2 + y^n-2 − z^n-2)
    //
    // and their combination
    //
    // fn(x,y,z) = f1,n(x,y,z) + f2,n(x,y,z) − f3,n(x,y,z)
    //
    // We call (x,y,z) a golden triple of order k if x, y, and z are all rational numbers of the 
    // form a / b with 0 < a < b ≤ k and there is (at least) one integer n, so that fn(x,y,z) = 0.
    //
    // Let s(x,y,z) = x + y + z.
    // Let t = u / v be the sum of all distinct s(x,y,z) for all golden triples (x,y,z) of order 35.
    // All the s(x,y,z) and t must be in reduced form.
    //
    // Find u + v.
    nombre limite = 35;
    std::set<fraction> fractions;
    for (nombre b = 2; b < limite + 1; ++b)
    for (nombre a = 1; a < b; ++a)
        fractions.insert(fraction(a, b));

    std::set<fraction> solutions;
    for (auto it1 = fractions.begin(), en = fractions.end(); it1 != en; ++it1)
    for (auto it2 = it1; it2 != en; ++it2)
    {
        auto x = *it1;
        auto y = *it2;
        // n = 1: z = x + y
        {
            fraction z = x+y;
            if (fractions.find(z) != fractions.end())
                solutions.insert(x+y+z);                 
        }
        
        // n = -1: 1/z = 1/x + 1/y
        {
            fraction z = x*y / (x + y);
            if (fractions.find(z) != fractions.end())
                solutions.insert(x+y+z);                 
        }
        
        {
            fraction zz = x*x+y*y;
            if (polygonal::est_carre(zz.numerator()) && polygonal::est_carre(zz.denominator()))
            {
                fraction z (racine_carre(zz.numerator()), racine_carre(zz.denominator()));
                {
                    // n = 2: z = sqrt(x^2+y^2)
                    if (fractions.find(z) != fractions.end())
                        solutions.insert(x+y+z);                 
                }
                
                {
                    // n = -2: z=x*y/sqrt(x^2+y^2)
                    z = x*y / z;
                    if (fractions.find(z) != fractions.end())
                        solutions.insert(x+y+z);
                }
            }
        }
    }
    
    grand_nombre u = 0;
    grand_nombre v = 1;
    for (auto s: solutions)
    {
        u = s.denominator()*u + s.numerator()*v;
        v *= s.denominator();
    }
    
    grand_nombre resultat = (u + v)/arithmetiques::PGCD(u,v);
    std::cout << "Solution: " << resultat << std::endl;
}
