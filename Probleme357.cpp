#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"

#include <iostream>
#include <vector>
#include <set>

typedef size_t nombre;

class Probleme357
{
	// Consider the divisors of 30: 1,2,3,5,6,10,15,30.
	// It can be seen that for every divisor d of 30, d+30/d is prime.

	// Find the sum of all positive integers n not exceeding 100 000 000
	// such that for every divisor d of n, d+n/d is prime.
	
    nombre              taille;
    std::set<nombre>    premiers;
	
	bool valide(nombre n)
	{
		for (nombre d = 2; d * d < n + 1; ++d)
		{
			if (n%d == 0)
			{
				if (n%(d*d) == 0) 
				    return false;
				if (premiers.find(n/d + d) == premiers.end()) 
				    return false;
			}			
		}
		return true;
	}
	
public:
	Probleme357(nombre t = 100000000L) : taille(t) {}
	
	void algorithme()
	{
		{
			Timer t("crible");
			premiers::crible(taille, premiers);
		}
		
		nombre solution = 0;
		{
			Timer t("algorithme");
			for (const nombre & p : premiers)
			{
				nombre n = p - 1;
				if (valide(n))
				{
					solution += n;
				}
			}
		}
		
		std::cout << "******************** SOLUTION ********************" << std::endl;
		std::cout << solution << std::endl;
	}
};

void probleme357()
{
	Probleme357 p;
	p.algorithme();
}
