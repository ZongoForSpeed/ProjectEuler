#include "problemes.h"
#include "utilitaires.h"

#include <set>
#include <numeric>
#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::mpz_int nombre;

ENREGISTRER_PROBLEME(346, "Strong Repunits")
{
	nombre limite = 1000000000000LL;
	nombre somme = 0;
	{
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
	return std::to_string(somme);
}
