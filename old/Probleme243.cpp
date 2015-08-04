// Problem 243
// A positive fraction whose numerator is less than its denominator is
// called a proper fraction.
// For any denominator, d, there will be d−1 proper fractions; for example, with d = 12:
// 1/12 , 2/12 , 3/12 , 4/12 , 5/12 , 6/12 , 7/12 , 8/12 , 9/12 , 10/12 , 11/12 .
//
// We shall call a fraction that cannot be cancelled down a resilient fraction.
// Furthermore we shall define the resilience of a denominator, R(d), to be the ratio of
// its proper fractions that are resilient; for example, R(12) = 4/11 .
// In fact, d = 12 is the smallest denominator having a resilience R(d) < 4/10 .
//
// Find the smallest denominator d, having a resilience R(d) < 15499/94744 .

#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>

#include <gmpxx.h>

typedef size_t nombre;

typedef std::list<nombre> vecteur;
typedef std::map<nombre, nombre> dictionnaire;

void crible(size_t taille, std::vector<bool>& premiers)
{
	premiers.assign(taille, true);
	premiers.at(0) = false;
	premiers.at(1) = false;

	for (nombre p = 2; p * p < taille; ++p)
	{
		if (premiers.at(p))
		{
			for (nombre k = p * p; k < taille; k += p)
			{
				premiers.at(k) = false;
			}
		}
	}
}


int main(int argc, char* argv[])
{
	size_t taille = 1000000000;
	std::vector<bool> premiers;

	crible(taille, premiers);

	mpz_class n = 1;
	mpz_class phi = 1;

	for (nombre p = 2; p < taille; ++p)
	{
		if (premiers.at(p))
		{

		}
	}

}

