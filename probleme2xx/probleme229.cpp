#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/dynamic_bitset.hpp>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(229, "Four Representations using Squares")
{
    // Consider the number 3600. It is very special, because
	//
	// 				3600 = 48² +   36²
	//				3600 = 20² + 2×40²
	//				3600 = 30² + 3×30²
	//				3600 = 45² + 7×15²
	//
	// Similarly, we find that 88201 = 99² + 280² = 287² + 2×54² = 283² + 3×52² = 1972 + 7×84².
	// 
	// In 1747, Euler proved which numbers are representable as a sum of two squares. We are interested 
	// in the numbers n which admit representations of all of the following four types:
	//
	//				n = a1² +   b1²
	//				n = a2² + 2 b2²
	//				n = a3² + 3 b3²
	//				n = a7² + 7 b7²,
	//
	// where the ak and bk are positive integers.
	//
	// There are 75373 such numbers that do not exceed 10^7.
	// How many such numbers are there that do not exceed 2×10^9?
	nombre taille = 2000000000ULL;
	boost::dynamic_bitset<> forme1(taille + 1, false);
	boost::dynamic_bitset<> forme2(taille + 1, false);
	boost::dynamic_bitset<> forme3(taille + 1, false);
	boost::dynamic_bitset<> forme7(taille + 1, false);
	
	for (nombre a = 1; a*a < taille; ++a)
	{
		const nombre aa = a*a;
		for (nombre b = 1; b <= a && aa + b*b <= taille; ++b)
		{
			const nombre bb = b*b;
			forme1.set(aa + bb);
			
			if (aa + 7*bb <= taille)
			{
				forme2.set(aa + 2*bb);
				forme3.set(aa + 3*bb);
				forme7.set(aa + 7*bb);
			}
			else if (aa + 3*bb <= taille)
			{
				forme2.set(aa + 2*bb);
				forme3.set(aa + 3*bb);
			}
			else if (aa + 2*bb <= taille)
			{
				forme2.set(aa + 2*bb);
			}
			
			if (7*aa + bb <= taille)
			{
				forme2.set(2*aa + bb);
				forme3.set(3*aa + bb);
				forme7.set(7*aa + bb);
			}
			else if (3*aa + bb <= taille)
			{
				forme2.set(2*aa + bb);
				forme3.set(3*aa + bb);
			}
			else if (2*aa + bb <= taille)
			{
				forme2.set(2*aa + bb);
			}
		}
	}
	
	forme1 &= forme2;
	forme1 &= forme3;
	forme1 &= forme7;

	nombre resultat = forme1.count();
	
    return std::to_string(resultat);
}
