#include "Probleme303.h"
#include "Timer.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;
typedef std::map<nombre, vecteur> dictionnaire;

class Probleme303
{
	nombre limite;
public:
	Probleme303(nombre _limite = 10000) : limite(_limite) {}
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
				for (const nombre & f : v)
				{
					nombre m = i * base + f;
					nombre mn = m*n;
					if (trinary(mn))
						return m;
					else if (trinary(mn%base))
						tmp.push_back(m);
				}		
			}
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
			for (nombre n = 1; n < limite + 1; ++n)
			{
				resultat += f(n);
			}
		}

		std::cout << "Resultat : " << resultat << std::endl;
    }
};

void probleme303()
{
	Probleme303 p;
	p.algorithme();
}
