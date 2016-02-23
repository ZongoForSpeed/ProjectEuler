#include "Problemes.h"
#include "Premiers.h"
#include "Puissance.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(132, "Large repunit factors")
{
    Timer t("probleme 132");
	// A number consisting entirely of ones is called a repunit. We shall define R(k) to be a repunit 
	// of length k.
    //
    // For example, R(10) = 1111111111 = 11×41×271×9091, and the sum of these prime factors is 9414.
    //
    // Find the sum of the first forty prime factors of R(109).
    nombre limite = 1000000;
    vecteur premiers;
    premiers::crible235<nombre>(limite, std::inserter(premiers, premiers.begin()));
    t.etape("fin crible");
    
    nombre compteur = 0;
	nombre resultat = 0;
	for (nombre p: premiers)
	{
	    if (puissance::puissance_modulaire(10ULL, 1000000000ULL, 9*p) == 1)
	    {
	        ++compteur;
	        resultat += p;
	        if (compteur == 40)
	            break;
	    }
	}
 	std::cout << "Solution: " << resultat << std::endl;
}

