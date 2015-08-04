#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <gmpxx.h>
#include <boost/foreach.hpp>

#include "Timer.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, nombre> dictionnaire;
#define foreach BOOST_FOREACH

class Probleme234
{
	// For an integer n ≥ 4, we define 
	// the lower prime square root of n, denoted by lps(n), as the largest prime ≤ √n 
	// and the upper prime square root of n, ups(n), as the smallest prime ≥ √n.

	// So, for example, lps(4) = 2 = ups(4), lps(1000) = 31, ups(1000) = 37.
	// Let us call an integer n ≥ 4 semidivisible, if one of lps(n) and ups(n) divides n, but not both.

	// The sum of the semidivisible numbers not exceeding 15 is 30, the numbers are 8, 10 and 12.
	// 15 is not semidivisible because it is a multiple of both lps(15) = 3 and ups(15) = 5.
	// As a further example, the sum of the 92 semidivisible numbers up to 1000 is 34825.

	// What is the sum of all semidivisible numbers not exceeding 999966663333 ?

	nombre limite;

public:
	Probleme234(nombre _limite) : limite(_limite) {}
	virtual ~Probleme234() {}

	void crible(nombre taille, vecteur & premiers)
	{
		std::vector<bool> test(taille + 1, true);
		test.at(0) = false;
		test.at(1) = false;

		for (nombre p = 2; p * p < taille + 1; ++p)
		{
			if (test.at(p))
			{
				for (nombre k = p * p; k < taille + 1; k += p) test.at(k) = false;
			}
		}

		for (nombre p = 0; p < taille + 1; ++p)
		{
			if (test.at(p)) premiers.push_back(p);
		}
	}

	nombre mpz2nombre (const mpz_class & z)
	{
		std::stringstream str;
		str << z;
		nombre n;
		str >> n;
		return n;
	}

	nombre calculBorne(nombre limite)
	{
		std::stringstream str;
		str << limite;
		mpz_class z(str.str());
		z = sqrt(z);
		mpz_class prime;
		mpz_nextprime(prime.get_mpz_t(), z.get_mpz_t());
		return mpz2nombre(prime);
	}

	void algorithme()
	{
		nombre borne = 0;
		{
			Timer t("Calcul borne");
			borne = calculBorne(limite);
			std::cout << borne << std::endl;
		}

		vecteur premiers;
		{
			Timer t("Crible d'Eratosthène");
			crible(borne, premiers);
		}

		nombre somme = 0;
		{
			Timer t("Algorithme");
			nombre p1 = premiers.front();
			foreach (nombre p2, premiers)
			{
				for (nombre n = p1*p1 + p1; n < std::min(p2*p2, limite); n += p1)
				{
					if (n%p2 != 0)
						somme += n;
				}
				for (nombre n = p2*p2 - p2; n > p1*p1; n -= p2)
				{
					if (n < limite && n%p1 != 0)
						somme += n;
				}

				p1 = p2;
			}
		}

		std::cout << "Resultat : " << somme << std::endl;
	}	
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme234 p(atoll(argv[1]));
	p.algorithme();
	
	return 0;
}