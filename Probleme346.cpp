#include "Probleme346.h"
#include "Timer.h"

#include <set>
#include <numeric>

#include "boost/multiprecision/cpp_int.hpp"

typedef boost::multiprecision::cpp_int nombre;

void probleme346()
{
	nombre limite = 1000000000000LL;
	nombre somme = 0;
	{
		Timer t("algorithme");
		std::set<nombre> ensemble;
		ensemble.insert(1);

		for (nombre base = 2; base * base + base + 1 <= limite; ++base)
		{
			nombre repunit = base * base + base + 1;
			while (repunit <= limite)
			{
				ensemble.insert(repunit);
				repunit = repunit * base + 1;
			}
		}

		somme = std::accumulate(ensemble.begin(), ensemble.end(), nombre(0));
	}

	std::cout << "Resultat: " << somme << std::endl;
}
