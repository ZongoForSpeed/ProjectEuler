#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <boost/rational.hpp>
#include <boost/multiprecision/gmp.hpp>

// typedef boost::multiprecision::mpz_int nombre;

typedef unsigned long long nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(243, "Odd Triplets")
{
    Timer timer("probleme 243");
    // A positive fraction whose numerator is less than its denominator is called a proper fraction.
	// For any denominator, d, there will be d−1 proper fractions; for example, with d = 12:
	// 1/12 , 2/12 , 3/12 , 4/12 , 5/12 , 6/12 , 7/12 , 8/12 , 9/12 , 10/12 , 11/12 .
	//
	// We shall call a fraction that cannot be cancelled down a resilient fraction.
	// 
	// Furthermore we shall define the resilience of a denominator, R(d), to be the ratio of its proper
	// fractions that are resilient; for example, R(12) = 4/11 .
	// 
	// In fact, d = 12 is the smallest denominator having a resilience R(d) < 4/10 .
	//
	// Find the smallest denominator d, having a resilience R(d) < 15499/94744 .
	const fraction objectif(15499, 94744);
	
	vecteur premiers;
	premiers::crible<nombre>(100, std::back_inserter(premiers));
	
	nombre resultat = 1;
	for (nombre p: premiers)
	{
		resultat *= p;
		fraction ratio(arithmetiques::phi(resultat, premiers), resultat - 1);
		if (ratio < objectif)
		{
			resultat /= p;
			break;
		}
	}
	
	for (nombre n = resultat;;n += resultat)
	{
		fraction ratio(arithmetiques::phi(n, premiers), n - 1);
		if (ratio < objectif)
		{
			resultat = n;
			break;
		}
	}

	std::cout << "Solution: " << resultat << std::endl;
}