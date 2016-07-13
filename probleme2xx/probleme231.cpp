#include "problemes.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
	nombre x(nombre n, nombre p)
	{
		nombre resultat = 0;
		while (n > 0)
		{
			n /= p;
			resultat += n;
		}
		
		return resultat;
	}
}

ENREGISTRER_PROBLEME(231, "The prime factorisation of binomial coefficients")
{
    // The binomial coefficient 10C3 = 120.
	// 120 = 23 × 3 × 5 = 2 × 2 × 2 × 3 × 5, and 2 + 2 + 2 + 3 + 5 = 14.
	// So the sum of the terms in the prime factorisation of 10C3 is 14. 
	//
	// Find the sum of the terms in the prime factorisation of 20000000C15000000.
	const nombre n = 20000000;
	const nombre k = 15000000;
	
	vecteur premiers;
	premiers::crible235<nombre>(n, std::back_inserter(premiers));
	
	nombre resultat = 0;
	for (nombre p: premiers)
	{
		resultat += p * (x(n,p) - x(k, p) - x(n - k, p));
	}
	
    return std::to_string(resultat);
}

