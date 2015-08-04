#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <boost/foreach.hpp>
#include <gmpxx.h>

#include "Timer.h"

//typedef long long nombre;
typedef mpz_class nombre;
typedef std::vector<nombre> vecteur;
typedef std::map<nombre, vecteur> dictionnaire;

// operator<<(std::ostream& os, const nombre & n)
// {
// 	mpz_out_str(&os, 10, n);
// 	// return os;
// }

#define foreach BOOST_FOREACH

class Probleme303
{
	nombre limite;
	
public:
	Probleme303(nombre _limite) : limite(_limite) {}
	virtual ~Probleme303() {}

	static bool trinary(nombre n)
	{
		while (n%10 < 3 && n > 10)
		{
			n /= 10;
		}
		return n%10 < 3;
	}

	nombre f(nombre n) const
	{
		nombre base = 1;
		vecteur v;
		v.push_back(0);
		nombre d = 0;
		while (true)
		{
			vecteur tmp;
			for (nombre i = 1; i < 11; ++i)
			{
				foreach (const nombre & f, v)
				{
					nombre m = i * base + f;
					nombre mn = m*n;
					if (trinary(mn))
						return m;
					else if (trinary(mn%base))
						tmp.push_back(m);
				}		
			}
			// std::cout << "(" << base << ") ";
			// foreach (const nombre & f, tmp)
			// {
			// 	std::cout << f*n << " ";
			// }
			// std::cout << std::endl;
			base *= 10;
			std::sort(tmp.begin(), tmp.end());
			std::swap(tmp, v);
		}
	}

    void algorithme()
    {
    	nombre resultat = 0;
		{
			Timer t("Algorithme");
			// nombre fn = f(limite);
			// std::cout << "f(" << limite << ") = " << fn * limite << std::endl;
			for (nombre n = 1; n < limite + 1; ++n)
			{
				nombre fn = f(n);
				std::cout << "f(" << n << ") = " << fn * n << std::endl;
				resultat += fn;
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
	
	Probleme303 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}
