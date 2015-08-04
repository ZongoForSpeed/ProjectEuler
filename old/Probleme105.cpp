// Probleme 105
//
// Let S(A) represent the sum of elements in set A of size n. We shall 
// call it a special sum set if for any two non-empty disjoint subsets, 
// B and C, the following properties are true:
// 
//    S(B) ≠ S(C); that is, sums of subsets cannot be equal.
//    If B contains more elements than C then S(B) > S(C).
//
// For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum 
// set because 65 + 87 + 88 = 75 + 81 + 84, whereas {157, 150, 164, 119,
// 79, 159, 161, 139, 158} satisfies both rules for all possible subset
// pair combinations and S(A) = 1286.
//
// Using sets.txt (right click and "Save Link/Target As..."), a 4K text 
// file with one-hundred sets containing seven to twelve elements 
// (the two examples given above are the first two sets in the file),
// identify all the special sum sets, A1, A2, ..., Ak, and find the value 
// of S(A1) + S(A2) + ... + S(Ak).
//
// NOTE: This problem is related to problems 103 and 106.

#include <cstdlib>
#include <cstdio>

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/algorithm/string.hpp>

class Probleme105 {
	std::ifstream m_fichier;
	size_t m_solution;
public:
	Probleme105(const std::string& fichier) : m_fichier(fichier.c_str(), std::ifstream::in), m_solution(0)
	{
	}
	        
	void algorithme()
	{
		while (m_fichier.eof() == false)
		{
			std::string ligne;
			std::getline(m_fichier, ligne);
			std::vector<std::string> champs;
			
			boost::split(champs, ligne, boost::is_any_of(","));
			// std::cout << "{" << ligne << "} = " << verifier(champs) <<  std::endl;
			
			std::cout << "{" << ligne << "} = " << (verifier(champs)?"true":"false") <<  std::endl;
		}	
		
		m_fichier.close();
		
		std::cout << "******** SOLUTION ********" << std::endl;
		std::cout << m_solution << std::endl;
	}
	
	bool verifier(const std::vector<std::string>& champs)
	{
		std::set<int> s;
		for (std::vector<std::string>::const_iterator it = champs.begin(), en = champs.end(); it != en; ++it)
		{
			s.insert(atoi(it->c_str()));
		}
		
		if (s.size() != champs.size())
			return false;
			
		size_t taille = s.size();			
		std::vector<int> v(s.begin(), s.end());
		
		if (v.front() + v.at(1) <= v.back())
			return false;
			
		if (taille > 4 && v.front() + v.at(1) + v.at(2) <= v.back() + v.at(taille - 2))
			return false;
			
		if (taille > 6 && v.front() + v.at(1) + v.at(2) + v.at(3) <= v.back() + v.at(taille - 2) + v.at(taille - 3))
			return false;
			
		if (taille > 8 && v.front() + v.at(1) + v.at(2) + v.at(3) + v.at(4) <= v.back() + v.at(taille - 2) + v.at(taille - 3) + v.at(taille - 4))
			return false;
			
		if (taille > 10 && v.front() + v.at(1) + v.at(2) + v.at(3) + v.at(4) + v.at(5) <= v.back() + v.at(taille - 2) + v.at(taille - 3) + v.at(taille - 4) + v.at(taille - 5))
			return false;
			
		for (size_t a1 = 0; a1 < taille; ++a1)
		for (size_t a2 = a1 + 2; a2 < taille; ++a2)
		for (size_t b1 = a1 + 1; b1 < a2; ++b1)
		for (size_t b2 = b1 + 1; b2 < taille; ++b2)
		if (a2 != b2)
		{
			if (v.at(a1) + v.at(a2) == v.at(b1) + v.at(b2))
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
				if (v.at(a1) + v.at(a2) + v.at(a3) == v.at(b1) + v.at(b2) + v.at(b3))
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
				if (v.at(a1) + v.at(a2) + v.at(a3) + v.at(a4) == v.at(b1) + v.at(b2) + v.at(b3) + v.at(b4))
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
				if (v.at(a1) + v.at(a2) + v.at(a3) + v.at(a4) + v.at(a5) == v.at(b1) + v.at(b2) + v.at(b3) + v.at(b4) + v.at(b5))
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
				if (v.at(a1) + v.at(a2) + v.at(a3) + v.at(a4) + v.at(a5) + v.at(a6) == v.at(b1) + v.at(b2) + v.at(b3) + v.at(b4) + v.at(b5) + v.at(b6))
					return false;
			}
		}
		
		for (std::vector<int>::const_iterator it = v.begin(), en = v.end(); it != en; ++it)
		{
			m_solution += *it;
		}
					
		return true;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " fichier" << std::endl;
		return 1;
	}
       
	Probleme105 p(argv[1]);
	
	p.algorithme();
    
       
	
       
	//for (size_t a = 0; a < taille; ++a)
	//for (size_t b = a + 1; b < taille; ++b)
	//for (size_t c = b + 1; c < taille; ++c)
	//for (size_t d = a + 1; d < taille; ++d) if (d != b && d < c)
	//for (size_t e = d + 1; e < taille; ++e) if (e != b && e != c)
	//for (size_t f = e + 1; f < taille; ++f) if (f != b && f != c)
	//{
		//std::string v1 = variable('V');
		//std::string v2 = variable('V');
	       
		//std::string b1 = variable('B');
	       
		//P << " C" << ++contraintes << ":"
		  //<< I.at(a) << " + " << I.at(b) << " + " << I.at(c);
		//P << " - " << I.at(d) << " - " << I.at(e) << " - " << I.at(f);
		//P << " + " << v1 << " - " << v2 << " = 0" << std::endl;
	       
		//P << " C" << ++contraintes << ":" << v1 << " - " << b1 << " > 0" << std::endl;
		//P << " C" << ++contraintes << ":" << v2 << " + " << b1 << " > 1" << std::endl;
		//P << " C" << ++contraintes << ":" << v1 << " - " << borne << b1 << " < 0" << std::endl;
		//P << " C" << ++contraintes << ":" << v2 << " + " << borne << b1 << " < " << borne << std::endl;
	       
		//variables.push_back(v1);
		//variables.push_back(v2);
	       
		//binaires.push_back(b1);
	//}
       
	//P << "Bounds" << std::endl;
	//for (std::vector<std::string>::const_iterator it = I.begin(), en = I.end(); it != en; ++it)
	//{
		//P << " 1 < " << *it << std::endl;
	//}
       
	//P << "General" << std::endl;
	//for (std::vector<std::string>::const_iterator it = I.begin(), en = I.end(); it != en; ++it)
	//{
		//P << " " << *it << std::endl;
	//}
       
	//P << "Binary" << std::endl;
	//for (std::vector<std::string>::const_iterator it = binaires.begin(), en = binaires.end(); it != en; ++it)
	//{
		//P << " " << *it << std::endl;
	//}

	//P << "End" << std::endl;
       
	//P.close();
       
	return 0;
}
