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
typedef std::set<nombre> ensemble;

void probleme131()
{
    Timer t("probleme 131");
	// There are some prime values, p, for which there exists a positive integer, n, such that the 
	// expression n^3 + n^2p is a perfect cube.
    //
    // For example, when p = 19, 8^3 + 8^2×19 = 12^3.
    // 
    // What is perhaps most surprising is that for each prime with this property the value of n is 
    // unique, and there are only four such primes below one-hundred.
    //
    // How many primes below one million have this remarkable property?
    nombre limite = 1000000;
    std::set<nombre> premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));
    t.etape("fin crible");
    
	nombre resultat = 0;
    for (nombre a = 1; 3*a*a < limite; ++a)
    {
        nombre b = a + 1;
        nombre p = b*b*b - a*a*a;
        if (p < limite && premiers.find(p) != premiers.end())
            ++resultat;
    }
    
    // 1) n^3 + n^2*p = n^2*(n + p), which, since p is prime can only be a perfect cube if both n and 
    // (n + p) are themselves perfect cubes; therefore p must be a difference of cubes.
    
    // 2) Since a^3 - b^3 = (a-b)(a^2 + ab + b^2), only the difference of consecutive cubes can be 
    // prime -- i.e. a - b = 1.
    
    // 3) So just check the (monotonically increasing) sequence of differences of consecutive cubes for primes.
  	std::cout << "Solution: " << resultat << std::endl;
}

