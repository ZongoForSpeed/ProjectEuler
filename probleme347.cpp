#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "polynome.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(347, "Largest integer divisible by two primes")
{
    // The largest integer ≤ 100 that is only divisible by both the primes 2 and
    // 3 is 96, as 96=32*3=25*3. For two distinct primes p and q let M(p,q,N) be
    // the largest positive integer ≤N only divisible by both p and q and M(p,q,N)=0
    // if such a positive integer does not exist.
	//
	// E.g. M(2,3,100)=96.
	// M(3,5,100)=75 and not 90 because 90 is divisible by 2 ,3 and 5.
	// Also M(2,73,100)=0 because there does not exist a positive integer ≤ 100 
	// that is divisible by both 2 and 73.
	// 
	// Let S(N) be the sum of all distinct M(p,q,N). S(100)=2262.
	//
	// Find S(10 000 000).
	const nombre limite = 10000000L + 1;
	std::vector<vecteur> facteurs(limite);
	for (size_t p = 2; p < limite; ++p)
	{
		if (facteurs[p].size() == 0)
		{
			for (size_t q = p; q < limite; q += p)
			{
				facteurs[q].push_back(p);
			}
		}
	}
	
	std::map<std::pair<nombre, nombre>, nombre> M;
	for (size_t p = 0; p < limite; ++p)
	{
		if (facteurs[p].size() == 2)
		{
			M[std::make_pair(facteurs[p].front(), facteurs[p].back())] = p;
		}
	}
	
    nombre resultat = 0;
	for (auto p: M)
	{
		resultat += p.second;
	}

    return std::to_string(resultat);
}
