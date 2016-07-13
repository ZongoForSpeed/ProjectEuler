#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>

typedef unsigned long long nombre;

ENREGISTRER_PROBLEME(120, "Square remainders")
{
    // Let r be the remainder when (a−1)^n + (a+1)^n is divided by a².
    //
    // For example, if a = 7 and n = 3, then r = 42: 63 + 83 = 728 ≡ 42 mod 49. And as n varies, 
    // so too will r, but for a = 7 it turns out that rmax = 42.
    //
    // For 3 ≤ a ≤ 1000, find ∑ rmax.
    nombre resultat = 0;
	for(nombre a = 3; a <= 1000; ++a)
		resultat += 2*a*((a*a - 1)/(2*a));
		
    return std::to_string(resultat);
}
