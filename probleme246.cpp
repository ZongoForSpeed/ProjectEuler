#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "timer.h"
#include "utilitaires.h"
#include "polygonal.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::pair<nombre, nombre> paire;

namespace
{
    class Probleme246
    {
    public:
        Probleme246()
        {
            a2 = 7500*7500;
            b2 = 2500*12500;
            
            // center of ellipse
            centre = std::make_pair(3000, 1500);
        }
        
        // paramètres del'ellipse
        long double a2; // demi-grand axe au carré
        long double b2; // demi-petit axe au carré
        
        paire centre;
        
        bool ellipse(nombre x, nombre y) 
        {
            // x^2/a^2 + y^2/b^2 - 1 <= 0
            // x^2*b^2 + y^2*a^2 - a^2*b^2 <= 0
            return (x - centre.first)*(x - centre.first)*b2 
                + (y - centre.second)*(y - centre.second)*a2 - a2*b2 <= 0;
        }
        
        bool keep(nombre ox, nombre oy) 
        {
            // change coordinates
            ox -= centre.first;
            oy -= centre.second;
            
            long double x = ox;
            long double y = oy;
            
            long double x0, y0;
            long double x1, y1;
            
            if (ox==0) 
            {
                y0 = y1 = b2/y;
                x0 = std::sqrt(a2*(1-y0*y0/b2));
                x1 = -x0;
            } 
            else if (oy==0)
            {
                x0 = x1 = a2/x;
                y0 = std::sqrt(b2*(1-x0*x0/a2));
                y1 = -y0;
            } 
            else if (std::abs(ox) < std::abs(oy))
            {
                // 2nd degree equation - looking for y
                long double a = a2*a2*y*y/(b2*b2*x*x) + a2/b2;
                long double b = -2*a2*a2*y/(b2*x*x);
                long double c = a2*a2/(x*x)-a2;
                
                long double delta = b*b - 4*a*c;
                
                y0 = (-b + std::sqrt(delta))/(2*a);
                y1 = (-b - std::sqrt(delta))/(2*a);
                
                x0 = (1 - y*y0/b2)*a2/x;
                x1 = (1 - y*y1/b2)*a2/x;
            } 
            else
            {
                // 2nd degree equation - looking for x
                long double a = b2*b2*x*x/(a2*a2*y*y) + b2/a2;
                long double b = -2*b2*b2*x/(a2*y*y);
                long double c = b2*b2/(y*y)-b2;
                
                long double delta = b*b - 4*a*c;
                
                x0 = (-b + std::sqrt(delta))/(2*a);
                x1 = (-b - std::sqrt(delta))/(2*a);
                
                y0 = (1 - x*x0/a2)*b2/y;
                y1 = (1 - x*x1/a2)*b2/y;
            }
            
            // scalar product
            long double norm0 = std::sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0));
            long double norm1 = std::sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1));
            
            long double prod = ( (x-x0)*(x-x1) + (y-y0)*(y-y1) ) / ( norm0 * norm1 );
            
            return prod < sqrt(1/2.);
        }
        
        nombre algorithme()
        {
            nombre y = centre.second;
            nombre xmin = centre.first;
            while (ellipse(xmin,y))
                xmin++;

            nombre xmax = xmin;
            while (keep(xmax+1,y)) 
            {
                xmax++;
            }
            
            nombre result = 0;
            
            do
            {
                if (y==centre.second)
                    result += (xmax-xmin+1)*2; // counted twice
                else
                {
                    // counted 4 times
                    result += (xmax-xmin+1)*4;
                    
                    // except for y axis (count twice)
                    if (xmin==centre.first)
                        result -= 2;
                }
                
                y++;
                
                while (xmin>centre.first && !ellipse(xmin-1,y)) 
                    xmin--;
                
                while (xmax>=centre.first && !keep(xmax,y)) 
                    xmax--;
            } 
            while (xmin < xmax);
            
            return result;
        }
    };
}

ENREGISTRER_PROBLEME(246, "Tangents to an ellipse")
{
    // A definition for an ellipse is:
    // Given a circle c with centre M and radius r and a point G such that d(G,M)<r,
    // the locus of the points that are equidistant from c and G form an ellipse.
    // 
    // The construction of the points of the ellipse is shown below.
    //
    // Given are the points M(-2000,1500) and G(8000,1500).
    // Given is also the circle c with centre M and radius 15000.
    // The locus of the points that are equidistant from G and c form an ellipse e.
    // From a point P outside e the two tangents t1 and t2 to the ellipse are drawn.
    // Let the points where t1 and t2 touch the ellipse be R and S.
    //
    // For how many lattice points P is angle RPS greater than 45 degrees?
    Probleme246 p;
	std::cout << "Solution: " << p.algorithme() << std::endl;
}
