#include "problemes.h"
#include "arithmetiques.h"
#include "timer.h"
#include "utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <memory>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

typedef std::shared_ptr<vecteur> foret;
typedef std::vector<foret> forets;

namespace
{
    nombre LaggedFibonacciGenerator(vecteur & cache, nombre n)
    {
        if (cache.empty())
        {
            cache.push_back(0);
            for (nombre k = 1; k < 56; ++k)
            {
                cache.push_back((100003 + 300007*k*k*k - 200003*k)%1000000);
            }
        }
        
        if (cache.size() <= n)
        {
            for (nombre k = cache.size(); k < n + 1000; ++k)
            {
                cache.push_back((cache[k - 24] + cache[k - 55])%1000000);
            }
        }
        
        return cache[n];
    }
    
    nombre Caller(vecteur & cache, nombre n)
    {
        return LaggedFibonacciGenerator(cache, 2*n - 1);
    }
    
    nombre Called(vecteur & cache, nombre n)
    {
        return LaggedFibonacciGenerator(cache, 2*n);
    }
    
    void merge(forets & f, foret & a, foret & b)
    {
	    if (a->size() > b->size())
	        merge(f, b, a);
		else
		{
			b->insert(b->end(), a->begin(), a->end());
			for (nombre k: *a)
				f[k] = b;
		}
    }
}

ENREGISTRER_PROBLEME(186, "Connectedness of a network")
{
    Timer timer("probleme 186");
    // Here are the records from a busy telephone system with one million users:
    //
    //                  RecNr   Caller  Called
    //                      1	200007	100053
    //                      2	600183	500439
    //                      3	600863	701497
    //                    ...      ...     ...
    //
    // The telephone number of the caller and the called number in record n are Caller(n) = S2n-1 and 
    // Called(n) = S2n where S1,2,3,... come from the "Lagged Fibonacci Generator":
    //
    // For 1 ≤ k ≤ 55, Sk = [100003 - 200003k + 300007k3] (modulo 1000000)
    // For 56 ≤ k, Sk = [Sk-24 + Sk-55] (modulo 1000000)
    //
    // If Caller(n) = Called(n) then the user is assumed to have misdialled and the call fails; otherwise
    // the call is successful.
    //
    // From the start of the records, we say that any pair of users X and Y are friends if X calls Y or 
    // vice-versa. Similarly, X is a friend of a friend of Z if X is a friend of Y and Y is a friend of Z; 
    // and so on for longer chains.
    //
    // The Prime Minister's phone number is 524287. After how many successful calls, not counting misdials,
    // will 99% of the users (including the PM) be a friend, or a friend of a friend etc., of the Prime Minister?
    nombre PrimeMinister = 524287;
	
    forets groupe;
    for (size_t n = 0; n < 1000000; ++n)
    {
    	foret f = std::make_shared<vecteur>();
    	f->push_back(n);
    	groupe.push_back(f);
    }
    nombre resultat = 0;
    vecteur cache;

    for (nombre n = 1, compteur = 0; compteur < 990000; ++n)
    {
        nombre i = Caller(cache, n);
        nombre j = Called(cache, n);
        if (i == j)
            continue;
            
        ++resultat;
        foret groupe_i = groupe[i];
        foret groupe_j = groupe[j];
        if (groupe_j->front() != groupe_i->front())
        {
			merge(groupe, groupe_i, groupe_j);
            compteur = groupe[PrimeMinister]->size();
        }
    }

    std::cout << "Solution: " << resultat << std::endl;
}
