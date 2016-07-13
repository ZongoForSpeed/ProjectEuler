#include "problemes.h"
#include "puissance.h"
#include "premiers.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(233, "Lattice points on a circle")
{
    // Let f(N) be the number of points with integer coordinates that are on a circle passing through
    // (0,0), (N,0),(0,N), and (N,N).
	//
	// It can be shown that f(10000) = 36 
	// 
	// What is the sum of all positive integers N ≤ 10^11 such that f(N) = 420 ?
	const nombre limite = puissance::puissance<nombre>(10, 11);

	vecteur premiers;
	premiers::crible235<nombre>(limite / ( puissance::puissance<nombre>(5, 3) * puissance::puissance<nombre>(13, 2) ), std::back_inserter(premiers));
	
	vecteur multi( limite / ( puissance::puissance<nombre>(5, 3) * puissance::puissance<nombre>(13, 2) * 17) + 1 );
	for (size_t c = 0; c < multi.size(); ++c)
		multi[c] = c;

	vecteur premiers4; // primes form of 4k+1
	for (nombre p: premiers)
	{
		if (p%4 == 1)
		{
			premiers4.push_back(p);
			for (size_t j = p; j < multi.size(); j += p)
				multi[j] = 0;
		}
	}

	for (size_t c = 1; c < multi.size(); c++) 
		multi[c] += multi[c-1];
	
	nombre resultat = 0;
	
	// n = p * q^2 * r^3
	for (nombre r: premiers4)
	{
		const nombre r3 = r*r*r;
		if (13 * 5 * 5 * r3 > limite) 
			break;
		
		for (nombre q: premiers4)
		{
			const nombre qq = q*q;
			if (5 * qq * r3 > limite) 
				break;
			
			if (r == q)	
				continue;
				
			for (nombre p: premiers4)
			{
				const nombre n = p * qq * r3;
				if (n > limite) 
					break;
				
				if (r == p || q == p) 
					continue;
					
				resultat += n * multi[ limite / n ];
			}
		}
	}
	
	// n = q^3 * r^7
	for (nombre r: premiers4)
	{
		const nombre r7 = puissance::puissance(r, 7);
		if (5*5*5 * r7 > limite)
			break;
			
		for (nombre q: premiers4)
		{
			const nombre n = q*q*q*r7;
			if (n > limite)
				break;
				
			if (r == q)
				continue;
			
			resultat += n * multi[ limite / n ];
		}
	}
	
	// n = q^2 * r^10
	for (nombre r: premiers4)
	{
		const nombre r10 = puissance::puissance(r, 10);
		if (5*5*r10 > limite)
			break;
			
		for (nombre q: premiers4)
		{
			const nombre n = q*q*r10;
			if (n > limite)
				break;
				
			if (r == q)
				continue;
				
			resultat += n * multi[ limite / n ];
		}
	}
	
    return std::to_string(resultat);
}

