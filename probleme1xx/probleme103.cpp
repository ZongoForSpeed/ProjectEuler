#include "problemes.h"
#include "arithmetiques.h"
#include "utilitaires.h"

#include <iostream>
#include <numeric>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace
{
    bool verifier(const vecteur & champs)
	{
	    const size_t taille = champs.size();
		if (champs.front() + champs.at(1) <= champs.back())
			return false;
			
		if (taille > 4 && champs.front() + champs.at(1) + champs.at(2) <= champs.back() + champs.at(taille - 2))
			return false;
			
		if (taille > 6 && champs.front() + champs.at(1) + champs.at(2) + champs.at(3) <= champs.back() + champs.at(taille - 2) + champs.at(taille - 3))
			return false;
			
		if (taille > 8 && champs.front() + champs.at(1) + champs.at(2) + champs.at(3) + champs.at(4) <= champs.back() + champs.at(taille - 2) + champs.at(taille - 3) + champs.at(taille - 4))
			return false;
			
		if (taille > 10 && champs.front() + champs.at(1) + champs.at(2) + champs.at(3) + champs.at(4) + champs.at(5) <= champs.back() + champs.at(taille - 2) + champs.at(taille - 3) + champs.at(taille - 4) + champs.at(taille - 5))
			return false;
			
		for (size_t a1 = 0; a1 < taille; ++a1)
		for (size_t a2 = a1 + 2; a2 < taille; ++a2)
		for (size_t b1 = a1 + 1; b1 < a2; ++b1)
		for (size_t b2 = b1 + 1; b2 < taille; ++b2)
		if (a2 != b2)
		{
			if (champs.at(a1) + champs.at(a2) == champs.at(b1) + champs.at(b2))
				return false;
		}

		if (taille > 5)
		{
			for (size_t a1 = 0; a1 < taille; ++a1)
			for (size_t a2 = a1 + 1; a2 < taille; ++a2)
			for (size_t a3 = a2 + 1; a3 < taille; ++a3)
			for (size_t b1 = a1 + 1; b1 < a3; ++b1) if (b1 != a2)
			for (size_t b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3)
			for (size_t b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3)
			{
				if (champs.at(a1) + champs.at(a2) + champs.at(a3) == champs.at(b1) + champs.at(b2) + champs.at(b3))
					return false;
			}

		}

		if (taille > 7)
		{
			for (size_t a1 = 0; a1 < taille; ++a1)
			for (size_t a2 = a1 + 1; a2 < taille; ++a2)
			for (size_t a3 = a2 + 1; a3 < taille; ++a3)
			for (size_t a4 = a3 + 1; a4 < taille; ++a4)
			for (size_t b1 = a1 + 1; b1 < a4; ++b1) if (b1 != a2 && b1 != a3)
			for (size_t b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4)
			for (size_t b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4)
			for (size_t b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4)
			{
				if (champs.at(a1) + champs.at(a2) + champs.at(a3) + champs.at(a4) == champs.at(b1) + champs.at(b2) + champs.at(b3) + champs.at(b4))
					return false;
			}
		}

		if (taille > 9)
		{
			for (size_t a1 = 0; a1 < taille; ++a1)
			for (size_t a2 = a1 + 1; a2 < taille; ++a2)
			for (size_t a3 = a2 + 1; a3 < taille; ++a3)
			for (size_t a4 = a3 + 1; a4 < taille; ++a4)
			for (size_t a5 = a4 + 1; a5 < taille; ++a5)
			for (size_t b1 = a1 + 1; b1 < a5; ++b1) if (b1 != a2 && b1 != a3 && b1 != a4)
			for (size_t b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4 && b2 != a5)
			for (size_t b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4 && b3 != a5)
			for (size_t b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4 && b4 != a5)
			for (size_t b5 = b4 + 1; b5 < taille; ++b5) if (b5 != a2 && b5 != a3 && b5 != a4 && b5 != a5)
			{
				if (champs.at(a1) + champs.at(a2) + champs.at(a3) + champs.at(a4) + champs.at(a5) == champs.at(b1) + champs.at(b2) + champs.at(b3) + champs.at(b4) + champs.at(b5))
					return false;
			}
		}

		if (taille > 11)
		{
			for (size_t a1 = 0; a1 < taille; ++a1)
			for (size_t a2 = a1 + 1; a2 < taille; ++a2)
			for (size_t a3 = a2 + 1; a3 < taille; ++a3)
			for (size_t a4 = a3 + 1; a4 < taille; ++a4)
			for (size_t a5 = a4 + 1; a5 < taille; ++a5)
			for (size_t a6 = a5 + 1; a6 < taille; ++a6)
			for (size_t b1 = a1 + 1; b1 < a6; ++b1) if (b1 != a2 && b1 != a3 && b1 != a4 && b1 != a5)
			for (size_t b2 = b1 + 1; b2 < taille; ++b2) if (b2 != a2 && b2 != a3 && b2 != a4 && b2 != a5 && b2 != a6)
			for (size_t b3 = b2 + 1; b3 < taille; ++b3) if (b3 != a2 && b3 != a3 && b3 != a4 && b3 != a5 && b3 != a6)
			for (size_t b4 = b3 + 1; b4 < taille; ++b4) if (b4 != a2 && b4 != a3 && b4 != a4 && b4 != a5 && b4 != a6)
			for (size_t b5 = b4 + 1; b5 < taille; ++b5) if (b5 != a2 && b5 != a3 && b5 != a4 && b5 != a5 && b5 != a6)
			for (size_t b6 = b5 + 1; b6 < taille; ++b6) if (b6 != a2 && b6 != a3 && b6 != a4 && b6 != a5 && b6 != a6)
			{
				if (champs.at(a1) + champs.at(a2) + champs.at(a3) + champs.at(a4) + champs.at(a5) + champs.at(a6) == champs.at(b1) + champs.at(b2) + champs.at(b3) + champs.at(b4) + champs.at(b5) + champs.at(b6))
					return false;
			}
		}
					
		return true;
	}
}

ENREGISTRER_PROBLEME(103, "Special subset sums: optimum")
{
    // Let S(A) represent the sum of elements in set A of size n. We shall call it a special sum set 
    // if for any two non-empty disjoint subsets, B and C, the following properties are true:
    //
    //      S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    //      If B contains more elements than C then S(B) > S(C).
    //
    // If S(A) is minimised for a given n, we shall call it an optimum special sum set. The first five
    // optimum special sum sets are given below.
    //
    // n = 1: {1}
    // n = 2: {1, 2}
    // n = 3: {2, 3, 4}
    // n = 4: {3, 5, 6, 7}
    // n = 5: {6, 9, 11, 12, 13}
    // 
    // It seems that for a given optimum set, A = {a1, a2, ... , an}, the next optimum set is of the 
    // form B = {b, a1+b, a2+b, ... ,an+b}, where b is the "middle" element on the previous row.
    // 
    // By applying this "rule" we would expect the optimum set for n = 6 to be A = {11, 17, 20, 22, 23, 24},
    // with S(A) = 117. However, this is not the optimum set, as we have merely applied an algorithm to 
    // provide a near optimum set. The optimum set for n = 6 is A = {11, 18, 19, 20, 22, 25}, with 
    // S(A) = 115 and corresponding set string: 111819202225.
    // 
    // Given that A is an optimum special sum set for n = 7, find its set string.
    // 
    // NOTE: This problem is related to Problem 105 and Problem 106.
    nombre minimum = std::numeric_limits<nombre>::max();
    vecteur solution;
    for (nombre a1 = 20; a1 < 50; ++a1)
    for (nombre a2 = a1 + 1; a2 < 50; ++a2)
    for (nombre a3 = a2 + 1; a3 < 50; ++a3)
    for (nombre a4 = a3 + 1; a4 < 50; ++a4)
    for (nombre a5 = a4 + 1; a5 < 50; ++a5)
    for (nombre a6 = a5 + 1; a6 < 50; ++a6)
    for (nombre a7 = a6 + 1; a7 < 100; ++a7)
    {
        const vecteur v { a1, a2, a3, a4, a5, a6, a7 };
        const nombre somme = std::accumulate(v.begin(), v.end(), 0UL);
        if (somme < minimum && verifier(v))
        {
            minimum = somme;
            solution = v;
            //std::cout << solution << " = " << minimum << std::endl;
        }
    }
    
    std::ostringstream oss;
    for (auto s: solution)
        oss << s;
    
    return oss.str();
}
