#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

#include <bitset>

// #include <boost/range/adaptor/reversed.hpp>
#include <boost/rational.hpp>
// #include <boost/multiprecision/gmp.hpp>
//
// typedef boost::multiprecision::mpz_int nombre;

typedef unsigned long long nombre;
typedef boost::rational<nombre> fraction;
typedef std::vector<nombre> vecteur;

namespace
{
/* void compute_primes(void) {
  primes.clear();
  primes.push_back(2);
  for (long long x = 3; x <= P; x+=2) {
    bool isprime = true;
    for (int i=0,n=primes.size();i<n;++i) {
      long long p = primes[i];
      if (p*p>x) break;
      if (x%p==0) {isprime=false; break;}
    }
    if (isprime) primes.push_back(x);
  }
}
*/

	bool est_premier(nombre n, const vecteur & premiers) 
	{
		for (const nombre p: premiers)
		{
			if (p*p > n)
				break;
			if (n%p == 0)
				return false;
		}
		return true;
	}

	nombre recherche(const vecteur & premiers, nombre limite, nombre n, nombre phi_n, nombre primes_left, nombre min_pidx) 
	{
		nombre resultat = 0;
		if (primes_left == 1) 
		{
			nombre min_p = premiers[min_pidx];
			nombre min_k = ((n*min_p-1) / (min_p*(n - phi_n) + phi_n)) + 1;
			nombre max_k = n / (n - phi_n);

			for (nombre k = min_k; k <= max_k; ++k) 
			{
				nombre numerateur = k*phi_n+1;
				nombre denominateur = n - k*(n-phi_n);
				
				if (denominateur==0)
					break;
					
				if (numerateur%denominateur == 0)
				{
					nombre candidat = numerateur/denominateur;
					
					if (candidat*n > limite)
						break;
						
					if (est_premier(candidat, premiers)) 
						resultat += n*candidat;
				}
			}
		} 
		else
		{
			for (size_t pidx = min_pidx + 1; pidx < premiers.size(); ++pidx) 
			{
				nombre borne = n;
				for (size_t i=0;i<primes_left;++i) borne*=premiers[pidx+i];
					
				if (borne > limite) break;
				nombre next_n = n*premiers[pidx], next_phi_n = phi_n*(premiers[pidx]-1);
				
				if (arithmetiques::PGCD(next_n, next_phi_n) != 1)
					continue;
				resultat += recherche(premiers, limite, next_n, next_phi_n, primes_left - 1, pidx);
			}
		}
		
		return resultat;
	}

}

ENREGISTRER_PROBLEME(245, "Coresilience")
{
    Timer timer("probleme 245");
    // We shall call a fraction that cannot be cancelled down a resilient fraction.
	// Furthermore we shall define the resilience of a denominator, R(d), to be the ratio of its proper
	// fractions that are resilient; for example, R(12) = 4/11.
	//
	// The resilience of a number d > 1 is then	φ(d) / d − 1, where φ is Euler's totient function.
	// We further define the coresilience of a number n > 1 as C(n)	= (n − φ(n)) / (n − 1)
	//
	// The coresilience of a prime p is C(p) = 1 / (p - 1)
	//
	// Find the sum of all composite integers 1 < n ≤ 2×1011, for which C(n) is a unit fraction.
	const nombre limite = 200000000000LL;
	const nombre P = std::sqrt(limite);
	
	vecteur premiers;
	premiers::crible235<nombre>(P, std::back_inserter(premiers));
	
	nombre resultat = 0;
	for (nombre i=2;;++i) 
	{
		const nombre somme = recherche(premiers, limite, 1, 1, i, 0);
		std::cout << "Somme nombre composite produit de " << i << " premiers = " << somme << std::endl;
		if (somme == 0) 
			break;
		resultat += somme;
	}

	std::cout << "Solution: " << resultat << std::endl;
}