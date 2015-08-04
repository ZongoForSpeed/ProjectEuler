#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
// #include <gmpxx.h>

typedef unsigned long long nombre;
typedef std::vector<unsigned short> vecteur;

void decomposition(nombre n, unsigned short base)
{
	std::string s;
	nombre test = 1;
	while(n != 0)
	{
		s.push_back('1' + n%base);
		test *= (n%base) + 1;
		n /= base;
	}
	
	std::reverse(s.begin(), s.end());
	std::cout << test << "\t" << s << "\t";
}

void affiche(const vecteur& v, unsigned short base)
{
	nombre n = v.size();
	std::cout << v.size() << "\t";
	nombre compteur = 0;
	for (vecteur::const_iterator it = v.begin(), en = v.end(); it != en; ++it)
	{
	/*
		if (*it == 0)
			std::cout << " ";
		else 
			std::cout << *it;
	*/
		if (*it != 0) ++compteur;
	}
	std::cout << compteur << "\t";
	
	decomposition(n - 1, base);
		
	for (vecteur::const_iterator it = v.begin(), en = v.end(); it != en; ++it)
	{
		if (*it == 0)
			std::cout << " ";
		else 
			std::cout << *it;
	}

	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << argv[0] << " taille base" << std::endl;
		return 1;
	}
		
	nombre taille = atoll(argv[1]);
	unsigned short base = atoi(argv[2]);
	
	/*vecteur precedent;
	
	for (nombre n = 0; n <= taille; ++n)
	{
		vecteur courant;
		courant.push_back(1);
		for (nombre p = 1; p < n; ++p)
		{
			unsigned short c = (precedent.at(p-1)+precedent.at(p))%base;
			courant.push_back(c);
		}
		if (n > 0)
			courant.push_back(1);
			
		affiche(courant, base);
		precedent = courant;
			
//		nombre compteur = 0;
	}
	*/
	
	nombre compteur = 0;
	
	for (nombre n = 0; n < taille; ++n)
	{
		nombre p = n;
		nombre r = 1;
		while (p != 0)
		{
			r *= (p%base) + 1;
			p /= base;
		}
		
		compteur += r;
	}
	
	std::cout << "********** SOLUTION **********" << std::endl;
	std::cout << compteur << std::endl;
	return 0;
}
