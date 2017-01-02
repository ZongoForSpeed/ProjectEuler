#include "problemes.h"
#include "utilitaires.h"
#include "grand_nombre.h"

#include <numeric>

ENREGISTRER_PROBLEME(146, "Investigating a Prime Pattern ")
{
	// The smallest positive integer n for which the numbers n²+1, n²+3, n²+7, n²+9, n²+13, and n²+27 
	// are consecutive primes is 10. The sum of all such integers n below one-million is 1242490.
    //
    // What is the sum of all such integers n below 150 million?
    size_t limite = 150000000ULL;
	size_t resultat = 0;
	
	for(size_t n = 10; n < limite; n += 10)
	{
		size_t reste = n%210;
		if (reste == 10 || reste == 80 || reste == 130 || reste == 200)
		{
			grand_nombre n2 = n*n;
			grand_nombre p = (n2+1);
			if (!p.premier())
			    continue;
			    
			p = p.premier_suivant();
			if (p != ( n2 + 3 ))
			    continue;

			p = p.premier_suivant();
			if (p != ( n2 + 7 ))
			    continue;

			p = p.premier_suivant();
			if (p != ( n2 + 9 ))
			    continue;

			p = p.premier_suivant();
			if (p != ( n2 + 13 ))
			    continue;

			p = p.premier_suivant();
			if( p == ( n2 + 27 )) 
			{
				std::cout << n << std::endl;
				resultat += n;
			}
		}
	}  
    return std::to_string(resultat);
}
