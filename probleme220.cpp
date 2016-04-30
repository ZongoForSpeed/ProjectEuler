#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
#include <complex>

// #include <boost/multiprecision/gmp.hpp>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    struct Point
    {
        std::complex<nombre> z;
        std::complex<nombre> d;

        void gauche()
        {
            d *= std::complex<nombre>(0, 1);
        }
        
        void droite()
        {
            d *= std::complex<nombre>(0, -1);
        }
        
        void avance()
        {
            z += d;
        }
        
        Point() : Point(0,0)
        {
        }
        
        Point(nombre _x, nombre _y, std::complex<nombre> _d = std::complex<nombre>(0, 1)) 
            : z(_x, _y), d(_d)
        {
        }
        
        Point & operator+=(const Point & p) 
        {
            z += p.z * d / std::complex<nombre>(0, 1);
            d *= p.d / std::complex<nombre>(0, 1);
        	return *this;
        }
    };
    
    Point operator+(Point lhs, const Point & rhs)
    {
        return lhs += rhs;
    }

}

ENREGISTRER_PROBLEME(220, "Heighway Dragon")
{
    // Let D0 be the two-letter string "Fa". For n≥1, derive Dn from Dn-1 by the string-rewriting
    // rules:
    //
    //                      "a" -> "aRbFR"
    //                      "b" -> "LFaLb"
    //
    // Thus, D0 = "Fa", D1 = "FaRbFR", D2 = "FaRbFRRLFaLbFR", and so on.
    //
    // These strings can be interpreted as instructions to a computer graphics program, with "F" 
    // meaning "draw forward one unit", "L" meaning "turn left 90 degrees", "R" meaning "turn right
    // 90 degrees", and "a" and "b" being ignored. The initial position of the computer cursor is 
    // (0,0), pointing up towards (0,1).
    //
    // Then Dn is an exotic drawing known as the Heighway Dragon of order n. For example, D10 is 
    // shown below; counting each "F" as one step, the highlighted spot at (18,16) is the position 
    // reached after 500 steps.
    //
    // What is the position of the cursor after 10^12 steps in D50 ?
    // Give your answer in the form x,y with no spaces.
    size_t longueur = 1000000000000LL;
    size_t dragon = 50;
    
    Point pl;
    pl.avance();
    pl.droite();
    pl.avance();
    pl.droite();
    
    Point pr;
    pr.avance();
    pr.gauche();
    pr.avance();
    pr.droite();
    
    std::vector<Point> DragonGauche { pl };
    std::vector<Point> DragonDroite { pr };
    
    for (size_t n = 0; n < dragon; ++n)
    {
        Point pl1 = DragonGauche.back();
        Point pl2 = DragonGauche.back();
        
        pr = DragonDroite.back();
        DragonGauche.push_back(pl1 + pr);
        
        pl2.gauche();
        pl2.gauche();
        
        DragonDroite.push_back(pl2 + pr);
    }
    
    auto c = chiffres::extraire_chiffres<size_t>(longueur, 2);
    Point resultat = DragonGauche[c.size() - 2];
    for (size_t i = 1; i < c.size() - 1; ++i)
    {
        if (c[i] == 1)
        {
            resultat += DragonGauche[c.size() - 2 - i];
            if (c[i - 1] == 1)
            {
                resultat.gauche();
                resultat.gauche();
            }
        }
    }

    std::cout << "Solution: " << resultat.z << std::endl;
}
