#include "problemes.h"
#include "utilitaires.h"

#include <iostream>
#include <cmath>
#include <limits>

namespace {
    long double calcul_intersection(long double m) {
        // cercle: (x-1)² + (y-1)² = 1
        //                  (y-1)² = 1 - (x-1)²
        //                   y-1   = sqrt(1 - (x-1)²)
        //                       y = 1 - sqrt(1 - (x-1)²)
        // ligne:                y = mx
        // intersection:        mx = 1 - sqrt(1 - (x-1)^2)
        //                       x = (m ± sqrt(2*m) + 1) / (m² + 1)
        return (m - std::sqrt(2*m) + 1) / (m*m + 1);
    }

    long double calcul_aire(unsigned int m)
    {
        long double slope = 1.0L / m;
        long double x = calcul_intersection(slope);
        long double y = slope * x;
        long double theta = std::asin(1 - x);
        
        return y * x / 2 + (y + 1) * (1 - x) / 2 - theta / 2;
    }
}

ENREGISTRER_PROBLEME(587, "Concave triangle") {
    // A square is drawn around a circle as shown in the diagram below on the left.
    // We shall call the blue shaded region the L-section.
    // A line is drawn from the bottom left of the square to the top right as shown in the diagram
    // on the right.
    // We shall call the orange shaded region a concave triangle.
    //
    // p587_concave_triangle_1.png
    // It should be clear that the concave triangle occupies exactly half of the L-section.
    //
    // Two circles are placed next to each other horizontally, a rectangle is drawn around both circles,
    // and a line is drawn from the bottom left to the top right as shown in the diagram below.
    //
    // p587_concave_triangle_2.png
    // This time the concave triangle occupies approximately 36.46% of the L-section.
    //
    // If n circles are placed next to each other horizontally, a rectangle is drawn around the n circles,
    // and a line is drawn from the bottom left to the top right, then it can be shown that the least 
    // value of n for which the concave triangle occupies less than 10% of the L-section is n = 15.
    //
    // What is the least value of n for which the concave triangle occupies less than 0.1% of the 
    // L-section?
    long double limit = 0.1L / 100;
    long double L = 1.0L - M_PI / 4.0L;
    
    unsigned int m = 1;
    unsigned int step = 64;
    
    while (true)
    {
        auto aire  = calcul_aire(m);
        auto ratio = aire / L;
        if (ratio < limit)
        {
            if (step == 1)
                break;
            
            m -= step;
            step /= 2;
        }
        
        m += step;
    }
  
    return std::to_string(m);
}
