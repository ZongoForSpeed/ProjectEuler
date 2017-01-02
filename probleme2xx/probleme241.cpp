#include "problemes.h"
#include "arithmetiques.h"
#include "premiers.h"
#include "grand_nombre.h"

#include <numeric>

#include <boost/rational.hpp>

typedef boost::rational<grand_nombre> fraction;
typedef std::vector<grand_nombre> vecteur;

namespace
{
	void solution(const vecteur & premiers, const grand_nombre limite, vecteur & resultat, grand_nombre n, fraction sigma)
	{
		std::map<grand_nombre, size_t> decomposition;
		arithmetiques::decomposition(sigma.numerator(), premiers, decomposition);
		
		grand_nombre p = decomposition.begin()->first;
		size_t exposant = decomposition.begin()->second;
		
		if (n % p == 0)
        	return;
		
		for (size_t a = exposant;; ++a)
		{
			grand_nombre m = n * grand_nombre::puissance(p, a);
			if (m > limite)
				break;
				
			fraction sigma2 = sigma * fraction(grand_nombre::puissance(p, a + 1) - 1, grand_nombre::puissance(p, a) * (p - 1));
				
			if (sigma2 == 1)
			{
				resultat.push_back(m);
				// std::cout << m << std::endl;
			}
			else if (sigma2.numerator() > 1 && sigma2.denominator() > 1)
			{
				solution(premiers, limite, resultat, m, sigma2);
			}
		}
	}
}

ENREGISTRER_PROBLEME(241, "Perfection Quotients")
{
    // For a positive integer n, let σ(n) be the sum of all divisors of n, so e.g. 
    // σ(6) = 1 + 2 + 3 + 6 = 12.
	//
	// A perfect number, as you probably know, is a number with σ(n) = 2n.
	// 
	// Let us define the perfection quotient of a positive integer as p(n) = σ(n)/n
	// 
	// Find the sum of all positive integers n ≤ 1018 for which p(n) has the form k + 1/2, where k is an
	// integer.
	const grand_nombre limite = grand_nombre::puissance(10, 18);
	vecteur premiers;
	premiers::crible235<grand_nombre>(1000, std::back_inserter(premiers));
	
	vecteur resultats;
	for (grand_nombre k = 1; k < 6; ++k)
		solution(premiers, limite, resultats, 1, fraction(2, 2*k+1));
		
	std::sort(resultats.begin(), resultats.end());
	std::cout << resultats << std::endl;

    grand_nombre resultat = std::accumulate(resultats.begin(), resultats.end(), grand_nombre(0));
    return resultat.to_string();
}
