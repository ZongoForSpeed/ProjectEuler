#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <gmpxx.h>
#include <limits>
#include <boost/foreach.hpp>
#include <complex>

#include "Timer.h"

typedef long long nombre;
typedef std::complex<nombre> complexe;
typedef std::vector<nombre> vecteur;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, nombre> dictionnaire;
#define foreach BOOST_FOREACH

class Probleme211
{
	// For a positive integer n, let σ2(n) be the sum of the squares of its divisors. For example,
	// σ2(10) = 1 + 4 + 25 + 100 = 130.

	// Find the sum of all n, 0 < n < 64,000,000 such that σ2(n) is a perfect square.

	nombre limite;
	
public:
	Probleme211(nombre _limite) : limite(_limite) {}
	virtual ~Probleme211() {}

	bool isSquare(nombre n)
	{
		nombre z = (nombre)sqrt((long double)n);
		return z*z == n;
	}
	
    // 100 ==> 43
    // 10000 ==> 36446
    // 100000 ==> 462294
    // 1000000 ==> 9890738
    void algorithme()
    {
    	nombre resultat = 1;
    	vecteur tableau;

    	{
    		Timer t("Initialisation tableau");
    		tableau.assign(limite, 1);
		}

		{
			Timer t("Calcul sigma2");
			for (nombre d = 2; d < limite; ++d) 
			{
				nombre d2 = d*d;
				for (nombre q = d; q < limite; q += d)
				{
					tableau[q] += d2;
				}

				if (isSquare(tableau[d]))
				{
					std::cout << d << std::endl;
					resultat += d;
				}
			}
		}
		
		std::cout << "Resultat : " << resultat << std::endl;
    }
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme211 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}
