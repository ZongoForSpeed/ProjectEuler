// Probleme 103
//
// Let S(A) represent the sum of elements in set A of size n. We shall call
// it a special sum set if for any two non-empty disjoint subsets, B and C,
// the following properties are true:
//
//     S(B) ≠ S(C); that is, sums of subsets cannot be equal.
//     If B contains more elements than C then S(B) > S(C).
//
// If S(A) is minimised for a given n, we shall call it an optimum special
// sum set. The first five optimum special sum sets are given below.
//
// n = 1: {1}
// n = 2: {1, 2}
// n = 3: {2, 3, 4}
// n = 4: {3, 5, 6, 7}
// n = 5: {6, 9, 11, 12, 13}
//
// It seems that for a given optimum set, A = {a1, a2, ... , an}, the next
// optimum set is of the form B = {b, a1+b, a2+b, ... ,an+b}, where b is
// the "middle" element on the previous row.
//
// By applying this "rule" we would expect the optimum set for n = 6 to be
// A = {11, 17, 20, 22, 23, 24}, with S(A) = 117. However, this is not the
// optimum set, as we have merely applied an algorithm to provide a near
// optimum set. The optimum set for n = 6 is A = {11, 18, 19, 20, 22, 25},
// with S(A) = 115 and corresponding set string: 111819202225.
//
// Given that A is an optimum special sum set for n = 7, find its set string.
//
// NOTE: This problem is related to problems 105 and 106.
#include <cstdlib>
#include <cstdio>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// class Probleme103 {
//        
// }

std::string variable(char symbole)
{
	static int variables = 0;
	std::ostringstream oss;
	oss << symbole << ++variables ;
	return oss.str();
}

int main(int argc, char**)
{
	int taille = 7;
	int borne = 300;
       
	std::ofstream P("p103-6.lp");
	P << "Minimize" << std::endl << " obj:";
       
	std::vector<std::string> I;
	std::vector<std::string> binaires;
	std::vector<std::string> variables;
	for (int i = 1; i <= taille; ++i)
	{
		if (i > 1) P << " + ";
		std::ostringstream oss;
		oss << "I" << i;
		I.push_back(oss.str());
		P << I.back();		
	}
       
	P << std::endl;
	P << "Subject To" << std::endl;
       
	int contraintes = 0;
	for (int i = 1; i < taille; ++i)
	{
		P << " C" << ++contraintes << ":"
		  << I.at(i - 1) << " - " << I.at(i) << " < -1" << std::endl;
	}
       
	P << " C" << ++contraintes << ":"
	  << I.front() << " + " << I.at(1) << " - " << I.back() << " > 1" << std::endl;
	P << " C" << ++contraintes << ":"
	  << I.front() << " + " << I.at(1) << " + " << I.at(2)
	  << " - " << I.at(taille - 2) << " - " << I.back() << " > 1" << std::endl;
	if (taille == 7)
	P << " C" << ++contraintes << ":"
	  << I.front() << " + " << I.at(1) << " + " << I.at(2) << " + " << I.at(3)
	  << " - " << I.at(taille - 3) << " - " << I.at(taille - 2) << " - " << I.back() << " > 1" << std::endl;
       
	for (size_t a = 0; a < taille; ++a)
	for (size_t b = a + 2; b < taille; ++b)
	for (size_t c = a + 1; c < taille; ++c)
	for (size_t d = c + 1; d < taille; ++d)
	if (b != c && b != d && (b > c || b > d))
	{
		std::string v1 = variable('V');
		std::string v2 = variable('V');
	       
		std::string b1 = variable('B');
		P << " C" << ++contraintes << ":"
		  << I.at(a) << " + " << I.at(b) << " - " << I.at(c) << " - " << I.at(d)
		  << " + " << v1 << " - " << v2 << " = 0" << std::endl;
	       
		P << " C" << ++contraintes << ":" << v1 << " - " << b1 << " > 0" << std::endl;
		P << " C" << ++contraintes << ":" << v2 << " + " << b1 << " > 1" << std::endl;
		P << " C" << ++contraintes << ":" << v1 << " - " << borne << b1 << " < 0" << std::endl;
		P << " C" << ++contraintes << ":" << v2 << " + " << borne << b1 << " < " << borne << std::endl;
	       
		variables.push_back(v1);
		variables.push_back(v2);
	       
		binaires.push_back(b1);
	}
       
	for (size_t a = 0; a < taille; ++a)
	for (size_t b = a + 1; b < taille; ++b)
	for (size_t c = b + 1; c < taille; ++c)
	for (size_t d = a + 1; d < taille; ++d) if (d != b && d < c)
	for (size_t e = d + 1; e < taille; ++e) if (e != b && e != c)
	for (size_t f = e + 1; f < taille; ++f) if (f != b && f != c)
	{
		std::string v1 = variable('V');
		std::string v2 = variable('V');
	       
		std::string b1 = variable('B');
	       
		P << " C" << ++contraintes << ":"
		  << I.at(a) << " + " << I.at(b) << " + " << I.at(c);
		P << " - " << I.at(d) << " - " << I.at(e) << " - " << I.at(f);
		P << " + " << v1 << " - " << v2 << " = 0" << std::endl;
	       
		P << " C" << ++contraintes << ":" << v1 << " - " << b1 << " > 0" << std::endl;
		P << " C" << ++contraintes << ":" << v2 << " + " << b1 << " > 1" << std::endl;
		P << " C" << ++contraintes << ":" << v1 << " - " << borne << b1 << " < 0" << std::endl;
		P << " C" << ++contraintes << ":" << v2 << " + " << borne << b1 << " < " << borne << std::endl;
	       
		variables.push_back(v1);
		variables.push_back(v2);
	       
		binaires.push_back(b1);
	}
       
	P << "Bounds" << std::endl;
	for (std::vector<std::string>::const_iterator it = I.begin(), en = I.end(); it != en; ++it)
	{
		P << " 1 < " << *it << std::endl;
	}
       
	P << "General" << std::endl;
	for (std::vector<std::string>::const_iterator it = I.begin(), en = I.end(); it != en; ++it)
	{
		P << " " << *it << std::endl;
	}
       
	P << "Binary" << std::endl;
	for (std::vector<std::string>::const_iterator it = binaires.begin(), en = binaires.end(); it != en; ++it)
	{
		P << " " << *it << std::endl;
	}

	P << "End" << std::endl;
       
	P.close();
       
	return 0;
}
