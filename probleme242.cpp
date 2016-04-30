#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"
#include "utilitaires.h"

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

namespace
{
	nombre c(nombre n)
	{
		// https://oeis.org/A159916
		nombre somme = chiffres::somme_chiffres<nombre>((n - 1)/4, 2);
		return puissance::puissance<nombre>(2, somme);
	}
	
	nombre triplets_impairs(nombre n)
	{
		if (n < 1)
			return 0;
		if (n == 1)
			return 1;
		if (n % 4 != 1)
			return triplets_impairs(n - (n + 3) % 4);
		if (n % 8 == 1)
	        return c(n) + triplets_impairs(n - 4);
	        
	    return 3 * triplets_impairs((n - 3) / 2);
	}
}

ENREGISTRER_PROBLEME(242, "Odd Triplets")
{
    // Given the set {1,2,...,n}, we define f(n,k) as the number of its k-element subsets with an odd 
    // sum of elements. For example, f(5,3) = 4, since the set {1,2,3,4,5} has four 3-element subsets
    // having an odd sum of elements, i.e.: {1,2,4}, {1,3,5}, {2,3,4} and {2,4,5}.
	//
	// When all three values n, k and f(n,k) are odd, we say that they make an odd-triplet [n,k,f(n,k)].
	//
	// There are exactly five odd-triplets with n ≤ 10, namely:
	// [1,1,f(1,1) = 1], [5,1,f(5,1) = 3], [5,5,f(5,5) = 1], [9,1,f(9,1) = 5] and [9,9,f(9,9) = 1].
	//
	// How many odd-triplets are there with n ≤ 1012 ?
	nombre resultat = triplets_impairs(puissance::puissance<nombre>(10, 12));
	std::cout << "Solution: " << resultat << std::endl;
}
