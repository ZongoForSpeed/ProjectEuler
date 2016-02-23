#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(148, "Exploring Pascal's triangle")
{
    Timer t("probleme 148");
	// We can easily verify that none of the entries in the first seven rows of Pascal's triangle are 
	// divisible by 7:
	//
	//  	  	  	  	  	  	 1
	//  	  	  	  	  	 1 	  	 1
	//  	  	  	  	 1 	  	 2 	  	 1
	//  	  	  	 1 	  	 3 	  	 3 	  	 1
	//  	  	 1 	  	 4 	  	 6 	  	 4 	  	 1
	//  	 1 	  	 5 	  	10 	  	10 	  	 5 	  	 1
	//	1 	  	 6 	  	15 	  	20 	  	15 	  	 6 	  	 1
	//
	// However, if we check the first one hundred rows, we will find that only 2361 of the 5050 entries 
	// are not divisible by 7.
	// 
	// Find the number of entries which are not divisible by 7 in the first one billion (109) rows of 
	// Pascal's triangle.
	nombre limite = 1000000000;
	nombre base = 7;
	nombre resultat = 0;
	for (nombre n = 0; n < limite; ++n)
	{
		nombre p = n;
		nombre r = 1;
		while (p != 0)
		{
			r *= p%base + 1;
			p /= base;
		}
		
		resultat += r;
	}

    std::cout << "Solution: " << resultat << std::endl;
}
