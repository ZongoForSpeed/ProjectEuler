#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(133)
{
    Timer t("probleme 133");
	// A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit of 
	// length k; for example, R(6) = 111111.
    //
    // Let us consider repunits of the form R(10n).
    // 
    // Although R(10), R(100), or R(1000) are not divisible by 17, R(10000) is divisible by 17. Yet there
    // is no value of n for which R(10n) will divide by 19. In fact, it is remarkable that 11, 17, 41, 
    // and 73 are the only four primes below one-hundred that can be a factor of R(10n).
    //
    // Find the sum of all the primes below one-hundred thousand that will never be a factor of R(10n).
    nombre limite = 100000;
    vecteur premiers;
    premiers::crible<nombre>(limite, std::inserter(premiers, premiers.begin()));
    t.etape("fin crible");
    
	nombre resultat = 0;
	for (nombre p: premiers)
	{
		if (p == 2 || p == 5)
		{
			resultat += p;
			continue;
		}
		nombre k = repunit::A(p);
		
		while (k%2 == 0) k /= 2;
		while (k%5 == 0) k /= 5;
		
		if (k != 1)
			resultat += p;
	}
 	std::cout << "Solution: " << resultat << std::endl;
}

