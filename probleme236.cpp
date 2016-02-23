#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef boost::rational<nombre> fraction;

ENREGISTRER_PROBLEME(236, "Luxury Hampers")
{
    Timer timer("probleme 236");
    // Suppliers 'A' and 'B' provided the following numbers of products for the luxury hamper market:
	//
	//									Product		'A'		'B'
	// 							  Beluga Caviar		5248	640
	//							 Christmas Cake		1312	1888
	// 							   Gammon Joint		2624	3776
	// 							   Vintage Port		5760	3776
	// 						 Champagne Truffles		3936	5664
	//
	// Although the suppliers try very hard to ship their goods in perfect condition, there is inevitably 
	// some spoilage - i.e. products gone bad.
	//
	// The suppliers compare their performance using two types of statistic:
	// 
	// 		- The five per-product spoilage rates for each supplier are equal to the number of products
	// 		gone bad divided by the number of products supplied, for each of the five products in turn.
	// 
	// 		- The overall spoilage rate for each supplier is equal to the total number of products gone 
	// 		bad divided by the total number of products provided by that supplier.
	// 
	// To their surprise, the suppliers found that each of the five per-product spoilage rates was worse 
	// (higher) for 'B' than for 'A' by the same factor (ratio of spoilage rates), m>1; and yet, paradoxically,
	// the overall spoilage rate was worse for 'A' than for 'B', also by a factor of m.
	// 
	// There are thirty-five m>1 for which this surprising result could have occurred, the smallest of which is 1476/1475.
	//
	// What's the largest possible value of m?
	// Give your answer as a fraction reduced to its lowest terms, in the form u/v.
	fraction resultat = 1;

    for(nombre b=1; b <= 640; b++)
    for(nombre k=3; k <= 1888 + 3776 + 5664; k++)
    {
        nombre a = 59*b;
        nombre r = 5*k;
        nombre pgcd = arithmetiques::PGCD(a, r);
        a /= pgcd;
        r /= pgcd;
        nombre end = std::min(5248 / a, (1312 + 2624 + 3936) / r);
        
        for(nombre t=1;t<=end;t++)
        {
            nombre u = 41*b;
            nombre v = 5*a*t;
            if(u > v)
            {
                nombre x = (a+r)*t;
                nombre y = b+k;
                nombre n = 246*59*u*v*x - 17405*u*u*y;
                nombre d = 17405*u*u - 246*90*v*v;
                if(n%d == 0)
                {
                    nombre h = n/d;
                    if(h <= 3776)
                    {
                        if((90*h*v)%(59*u)==0)
                        {
              	        	fraction ratio(u, v);
              	        	if (ratio > resultat)
              	        		resultat = ratio;
                        }
                    }
                }
            }
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}
