#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

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
    nombre LaggedFibonacciGenerator(nombre n)
    {
        static vecteur S;
        if (S.empty())
        {
            S.push_back(0);
            for (nombre k = 1; k < 56; ++k)
            {
                S.push_back((100003 + 300007*k*k*k - 200003*k)%1000000);
            }
        }
        
        if (S.size() <= n)
        {
            for (nombre k = S.size(); k < n + 1000; ++k)
            {
                S.push_back((S[k - 24] + S[k - 55])%1000000);
            }
        }
        
        return S[n];
    }
    
    nombre Caller(nombre n)
    {
        return LaggedFibonacciGenerator(2*n - 1);
    }
    
    nombre Called(nombre n)
    {
        return LaggedFibonacciGenerator(2*n);
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

ENREGISTRER_PROBLEME(186)
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
    for (nombre n = 1, compteur = 0; compteur < 990000; ++n)
    {
        nombre i = Caller(n);
        nombre j = Called(n);
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
