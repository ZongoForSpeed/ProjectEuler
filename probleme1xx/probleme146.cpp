#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <gmpxx.h>

typedef mpz_class nombre;

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
			nombre n2 = n;
			n2 = n2 * n;
			nombre k = (n2+1);
			if (!mpz_probab_prime_p(k.get_mpz_t(),5))
			    continue;
			    
			nombre next;
			nombre curr = k;
			mpz_nextprime(next.get_mpz_t(), curr.get_mpz_t());
			if (next != ( n2 + 3 ))
			    continue;
			    
			curr = next;
			mpz_nextprime(next.get_mpz_t(), curr.get_mpz_t());
			if (next != ( n2 + 7 ))
			    continue;
			    
			curr = next;
			mpz_nextprime(next.get_mpz_t(), curr.get_mpz_t());
			if (next != ( n2 + 9 ))
			    continue;
			    
			curr = next;
			mpz_nextprime(next.get_mpz_t(), curr.get_mpz_t());
			if (next != ( n2 + 13 ))
			    continue;
			    
			curr = next;
			mpz_nextprime(next.get_mpz_t() , curr.get_mpz_t());
			if( next == ( n2 + 27 )) 
			{
				std::cout << n << std::endl;
				resultat += n;
			}
		}
	}  
    std::cout << "Solution: " << resultat << std::endl;
}
