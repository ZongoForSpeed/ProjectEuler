#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(137, "Fibonacci golden nuggets")
{
    // Consider the infinite polynomial series AF(x) = xF1 + x2F2 + x3F3 + ..., where Fk is the kth 
    // term in the Fibonacci sequence: 1, 1, 2, 3, 5, 8, ... ; that is, Fk = Fk−1 + Fk−2, F1 = 1 and
    // F2 = 1.
    //
    // For this problem we shall be interested in values of x for which AF(x) is a positive integer.
    // 
    // Surprisingly AF(1/2) = (1/2).1 + (1/2)2.1 + (1/2)3.2 + (1/2)4.3 + (1/2)5.5 + ...
 	//                      = 1/2 + 1/4 + 2/8 + 3/16 + 5/32 + ...
 	//                      = 2
    //
    // The corresponding values of x for the first five natural numbers are shown below.
    //
    //                                      x       	AF(x)
    //                                      √2−1	    1
    //                                      1/2	        2
    //                                      (√13−2)/3	3
    //                                      (√89−5)/8	4
    //                                      (√34−3)/5	5
    // 
    // We shall call AF(x) a golden nugget if x is rational, because they become increasingly rarer; 
    // for example, the 10th golden nugget is 74049690.
    // 
    // Find the 15th golden nugget.
    nombre objectif = 15;
    nombre resultat = 0;
    
    std::pair<nombre, nombre> f(1, 2);
    for (nombre k = 1;; ++k)
    {
        if (k == objectif)
        {
            resultat = f.first * f.second;
            break;
        }
        f = std::make_pair(f.first + f.second, f.first + 2*f.second);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}

