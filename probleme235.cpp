#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
	long double S(long double r)
	{
		long double s = 0.0;
		for (size_t k = 1; k <= 5000; ++k)
		{
			s += (900.0 - 3.0 * k) * puissance::puissance(r, k - 1);
		}
		
		return s;
	}
}

ENREGISTRER_PROBLEME(235, "An Arithmetic Geometric sequence")
{
    Timer timer("probleme 235");
    // Given is the arithmetic-geometric sequence u(k) = (900-3k)rk-1.
	// Let s(n) = Σk=1...nu(k).
	// 
	// Find the value of r for which s(5000) = -600,000,000,000.
	// 
	//Give your answer rounded to 12 places behind the decimal point.
	const long double objectif = -600000000000;
	long double r = 1.0;
	long double dr = 0.125;
	
	long double s = 0.0;
	while (std::abs(s - objectif) > 1.0)
	{
		s = S(r);
		if (s > objectif)
			r += dr;
		else 
			r -= dr;
			
		dr /= 2;
	}
	std::cout << std::setprecision(13);
    std::cout << "Solution: " << r << std::endl;
}
