#include "problemes.h"
#include "arithmetiques.h"
#include "combinatoire.h"
#include "premiers.h"
#include "puissance.h"
#include "utilitaires.h"
#include "timer.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(296, "Angular Bisector and Tangent")
{
    // Given is an integer sided triangle ABC with BC ≤ AC ≤ AB.
	// k is the angular bisector of angle ACB.
	// m is the tangent at C to the circumscribed circle of ABC.
	// n is a line parallel to m through B.
	// The intersection of n and k is called E.
	//
	// p296_bisector.gif
	// How many triangles ABC with a perimeter not exceeding 100 000 exist such 
	// that BE has integral length?
	nombre n = 100000;
    nombre resultat = 0;
	for (nombre a = 1; 3*a <= n; ++a) 
	for (nombre b = a; a + 2*b <= n; ++b) 
	{
		nombre d = (a + b) / arithmetiques::PGCD(a, b);
		nombre cmin = b;
		nombre cmax = std::min(a + b - 1, n - a - b);
		resultat += cmax / d - (cmin - 1) / d;
	}

    return std::to_string(resultat);
}
