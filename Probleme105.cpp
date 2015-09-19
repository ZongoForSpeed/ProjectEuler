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

void probleme105()
{
    Timer t("probleme 105");
    // Let S(A) represent the sum of elements in set A of size n. We shall call it a special sum set
    // if for any two non-empty disjoint subsets, B and C, the following properties are true:
    //
    //      S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    //      If B contains more elements than C then S(B) > S(C).
    // For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum set because 
    // 65 + 87 + 88 = 75 + 81 + 84, whereas {157, 150, 164, 119, 79, 159, 161, 139, 158} satisfies both
    // rules for all possible subset pair combinations and S(A) = 1286.
    //
    // Using sets.txt (right click and "Save Link/Target As..."), a 4K text file with one-hundred sets 
    // containing seven to twelve elements (the two examples given above are the first two sets in the file),
    // identify all the special sum sets, A1, A2, ..., Ak, and find the value of S(A1) + S(A2) + ... + S(Ak).
    //
    // NOTE: This problem is related to Problem 103 and Problem 106.
    std::ifstream ifs("data/p105_sets.txt");
    nombre resultat = 0;
    std::string ligne;
    while (ifs >> ligne)
    {
        std::vector<std::string> v;
        boost::split(v,ligne,boost::is_any_of(","));
        
        vecteur set;
        for (auto s: v) set.push_back(std::stoull(s));
            
        std::sort(set.begin(), set.end());
        if (verifier(set))
            resultat += std::accumulate(set.begin(), set.end(), 0ULL);
    }
    
    std::cout << "Solution: " << resultat << std::endl;
}
