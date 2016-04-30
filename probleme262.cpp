#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "utilitaires.h"
#include "diophantienne.h"

#include <iostream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    long double h(long double x, long double y)
    {
        return ( 5000.0 - 0.005*(x*x + y*y + x*y) + 12.5*(x + y) ) 
            * std::exp( - std::abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) );
    }
    
    long double dh_dx(long double x, long double y)
    {
        return (h(x + 0.000001, y) - h(x - 0.000001, y)) / 0.000002;
    }

    long double dichotomie(std::function<long double(long double)> f, long double x_inf, long double x_sup)
    {
        long double f_inf = f(x_inf);
        long double f_sup = f(x_sup);
        
        while(x_sup - x_inf > 0.0000000001)
        {
            long double x_med = (x_sup + x_inf) / 2;
            long double f_med = f(x_med);
            
            if (f_med < 0)
            {
                x_sup = x_med;
                f_sup = f_med;
            }
            else
            {
                x_inf = x_med;
                f_inf = f_med;
            }
        }
        
        return (x_inf + x_sup) / 2;
    }
    
    long double marche(long double xmin, long double fmin, long double objectif_x, long double objectif_y, long double pas)
    {
        long double d = 0.0;
        long double x0 = xmin;
        long double y0 = 0.0;
        boost::optional<long double> t0;
        long double alpha = xmin;
        
        while (true)
        {
            alpha += pas;
            long double x = dichotomie([&](long double _x) { return h(_x, alpha - _x) - fmin; }, x0 - 5, x0 + 5);
            long double y = alpha - x;
            
            long double dy_dx = (y - y0) / (x - x0);
            long double tangente = y + dy_dx * (objectif_x - x) - objectif_y;
            
            if (t0 && *t0 * tangente < 0 and std::abs(tangente) < 100)
            {
                return d + std::sqrt((x0-objectif_x)*(x0-objectif_x)+(y0-objectif_y)*(y0-objectif_y));
            }
            
            d += std::sqrt((x0-x)*(x0-x) + (y0-y)*(y0-y));
            x0 = x;
            y0 = y;
            t0 = tangente;
        }
    }
}

ENREGISTRER_PROBLEME(262, "Mountain Range")
{
    // The following equation represents the continuous topography of a mountainous
    // region, giving the elevation h at any point (x,y):
    //
    //                             p262_formula1.gif
    //
    // A mosquito intends to fly from A(200,200) to B(1400,1400), without leaving
    // the area given by 0 ≤ x, y ≤ 1600.
    //
    // Because of the intervening mountains, it first rises straight up to a point
    // A', having elevation f. Then, while remaining at the same elevation f, it
    // flies around any obstacles until it arrives at a point B' directly above B.
    // 
    // First, determine fmin which is the minimum constant elevation allowing 
    // such a trip from A to B, while remaining in the specified area.
    // Then, find the length of the shortest path between A' and B', while flying
    // at that constant elevation fmin.
    //
    // Give that length as your answer, rounded to three decimal places.
    //
    // Note: For convenience, the elevation function shown above is repeated below,
    // in a form suitable for most programming languages:
    // h = ( 5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ) 
    //   * exp( -abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) )
    // auto dh = ;
    std::cout << std::fixed << std::setprecision(3);
    // std::cout << "h(A) = " << h(200, 200) << std::endl;
    // std::cout << "h(B) = " << h(1400, 1400) << std::endl;

    long double xmin = dichotomie([](long double x) /*-> long double*/ { return dh_dx(x, 0); }, 0.0, 1600.0);
    long double fmin = h(xmin, 0.0);
    
    // std::cout << xmin << ", " << fmin << std::endl;
    
    long double resultat = marche(xmin, fmin, 200, 200, -1.0)
        + marche(xmin, fmin, 1400, 1400, 1.0);
    
    std::cout << "Solution: " << resultat << std::endl;
}
