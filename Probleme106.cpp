#include "Problemes.h"
#include "Arithmetiques.h"
#include "Timer.h"
#include "Utilitaires.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(106, "Special subset sums: meta-testing")
{
    Timer t("probleme 106");
    // Let S(A) represent the sum of elements in set A of size n. We shall call it a special sum set
    // if for any two non-empty disjoint subsets, B and C, the following properties are true:
    //
    //      S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    //      If B contains more elements than C then S(B) > S(C).
    //
    // For this problem we shall assume that a given set contains n strictly increasing elements and
    // it already satisfies the second rule.
    //
    // Surprisingly, out of the 25 possible subset pairs that can be obtained from a set for which 
    // n = 4, only 1 of these pairs need to be tested for equality (first rule). Similarly, 
    // when n = 7, only 70 out of the 966 subset pairs need to be tested.
    //
    // For n = 12, how many of the 261625 subset pairs that can be obtained need to be tested for 
    // equality?
    //
    // NOTE: This problem is related to Problem 103 and Problem 105.
	nombre taille = 12;
	nombre resultat = 0;
	for (nombre a1 = 0; a1 < taille; ++a1)
	for (nombre a2 = a1 + 2; a2 < taille; ++a2)
	for (nombre b1 = a1 + 1; b1 < a2; ++b1)
	for (nombre b2 = b1 + 1; b2 < a2; ++b2)
	{
		// std::cout << "I" << a1 << " + I" << a2 << " ≠ " << "I" << b1 << " + I" << b2 << std::endl;
		++resultat;
	}

	if (taille > 5)
	{
		for (nombre a1 = 0; a1 < taille; ++a1)
		for (nombre a2 = a1 + 1; a2 < taille; ++a2)
		for (nombre a3 = a2 + 1; a3 < taille; ++a3)
		for (nombre b1 = a1 + 1; b1 < a3; ++b1) if (b1 != a2)
		for (nombre b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3)
		for (nombre b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3)
		if (a2 > b2 || a3 > b3)
		{
			// std::cout << "I" << a1 << " + I" << a2 << " + I" << a3 << " ≠ " << "I" << b1 << " + I" << b2 << " + I" << b3 << std::endl;
			++resultat;
		}

	}

	if (taille > 7)
	{
		for (nombre a1 = 0; a1 < taille; ++a1)
		for (nombre a2 = a1 + 1; a2 < taille; ++a2)
		for (nombre a3 = a2 + 1; a3 < taille; ++a3)
		for (nombre a4 = a3 + 1; a4 < taille; ++a4)
		for (nombre b1 = a1 + 1; b1 < a4; ++b1) if (b1 != a2 && b1 != a3)
		for (nombre b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4)
		for (nombre b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4)
		for (nombre b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4)
		if (a2 > b2 || a3 > b3 || a4 > b4)
		{
			// std::cout << "I" << a1 << " + I" << a2 << " + I" << a3 << " + I" << a4 << " ≠ " 
			//           << "I" << b1 << " + I" << b2 << " + I" << b3 << " + I" << b4 << std::endl;
			++resultat;
		}
	}

	if (taille > 9)
	{
		for (nombre a1 = 0; a1 < taille; ++a1)
		for (nombre a2 = a1 + 1; a2 < taille; ++a2)
		for (nombre a3 = a2 + 1; a3 < taille; ++a3)
		for (nombre a4 = a3 + 1; a4 < taille; ++a4)
		for (nombre a5 = a4 + 1; a5 < taille; ++a5)
		for (nombre b1 = a1 + 1; b1 < a5; ++b1) if (b1 != a2 && b1 != a3 && b1 != a4)
		for (nombre b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4 && b2 != a5)
		for (nombre b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4 && b3 != a5)
		for (nombre b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4 && b4 != a5)
		for (nombre b5 = b4 + 1; b5 < taille; ++b5) if (b5 != a2 && b5 != a3 && b5 != a4 && b5 != a5)
		if (a2 > b2 || a3 > b3 || a4 > b4 || a5 > b5)
		{
			// std::cout << "I" << a1 << " + I" << a2 << " + I" << a3 << " + I" << a4 << " + I" << a5<< " ≠ " 
			//           << "I" << b1 << " + I" << b2 << " + I" << b3 << " + I" << b4 << " + I" << b5 << std::endl;
			++resultat;
		}
	}

	if (taille > 11)
	{
		for (nombre a1 = 0; a1 < taille; ++a1)
		for (nombre a2 = a1 + 1; a2 < taille; ++a2)
		for (nombre a3 = a2 + 1; a3 < taille; ++a3)
		for (nombre a4 = a3 + 1; a4 < taille; ++a4)
		for (nombre a5 = a4 + 1; a5 < taille; ++a5)
		for (nombre a6 = a5 + 1; a6 < taille; ++a6)
		for (nombre b1 = a1 + 1; b1 < a6; ++b1) if (b1 != a2 && b1 != a3 && b1 != a4 && b1 != a5)
		for (nombre b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4 && b2 != a5 && b2 != a6)
		for (nombre b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4 && b3 != a5 && b3 != a6)
		for (nombre b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4 && b4 != a5 && b4 != a6)
		for (nombre b5 = b4 + 1; b5 < taille; ++b5) if (b5 != a2 && b5 != a3 && b5 != a4 && b5 != a5 && b5 != a6)
		for (nombre b6 = b5 + 1; b6 < taille; ++b6) if (b6 != a2 && b6 != a3 && b6 != a4 && b6 != a5 && b6 != a6)
		if (a2 > b2 || a3 > b3 || a4 > b4 || a5 > b5 || a6 > b6)
		{
			// std::cout << "I" << a1 << " + I" << a2 << " + I" << a3 << " + I" << a4 << " + I" << a5 << " + I" << a6 << " ≠ " 
			//	  << "I" << b1 << " + I" << b2 << " + I" << b3 << " + I" << b4 << " + I" << b5 << " + I" << b6 << std::endl;
			++resultat;
		}
	}
	
	std::cout << "Solution: " << resultat << std::endl;
}
