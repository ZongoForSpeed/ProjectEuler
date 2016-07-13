#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

ENREGISTRER_PROBLEME(150, "Searching a triangular array for a sub-triangle having minimum-sum")
{
	// In a triangular array of positive and negative integers, we wish to find a sub-triangle such that
	// the sum of the numbers it contains is the smallest possible.
    //
    // In the example below, it can be easily verified that the marked triangle satisfies this condition
    // having a sum of −42.
    //
    // matrice m { {15},
    //             {-14, -7},
    //             {20, -13, -5},
    //             {-3, 8, 23, -26},
    //             {1, -4, -5, -18, 5},
    //             {-16, 31, 2, 9, 28, 3}
    //           };
    // 
    // We wish to make such a triangular array with one thousand rows, so we generate 500500 pseudo-random
    // numbers sk in the range ±2^19, using a type of random number generator (known as a Linear Congruential
    // Generator) as follows:
    //
    //      t := 0 
    //      for k = 1 up to k = 500500: 
    //          t := (615949*t + 797807) modulo 2^20
    //          sk := t−2^19
    //
    //Thus: s1 = 273519, s2 = −153582, s3 = 450905 etc
    //
    //Our triangular array is then formed using the pseudo-random numbers thus:
    //
    //                                      s1
    //                                    s2  s3
    //                                  s4  s5  s6  
    //                                s7  s8  s9  s10
    //                              ...
    //
    // Sub-triangles can start at any element of the array and extend down as far as we like (taking-in 
    // the two elements directly below it from the next row, the three elements directly below from the
    // row after that, and so on). 
    // The "sum of a sub-triangle" is defined as the sum of all the elements it contains. 
    // Find the smallest possible sub-triangle sum.
	nombre deux20 = 1 << 20;
	nombre deux19 = 1 << 19;
	nombre t = 0;
	
	matrice m;
	vecteur ligne;
	for (size_t k = 0; k < 500500; ++k)
	{
	    t = (615949*t + 797807)%deux20;
	    ligne.push_back(t - deux19);
	    if (ligne.size() > m.size())
	    {
	        m.push_back(ligne);
	        ligne.clear();
	    }
	}

	nombre resultat = 0;
    for (size_t i = 0; i < m.size(); ++i)
    {
        for (size_t j = 0; j < i + 1; ++j)
        {
            nombre somme = 0;
            for (size_t k = i; k < m.size(); ++k)
            {
                const vecteur & l = m[k];
                somme += std::accumulate(std::next(l.begin(), j), 
                                         std::next(l.begin(), k - i + j + 1), 0LL);
                resultat = std::min(resultat, somme);
            }
        }
    }
    return std::to_string(resultat);
}
