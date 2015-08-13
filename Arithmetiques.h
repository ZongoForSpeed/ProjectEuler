#pragma once

#include <vector>
#include <set>
#include <list>

namespace arithmetiques
{
    template<typename N>
    N PGCD(N a, N b)
	{
		N pgcd = 0;
		while (true)
		{
			pgcd = a % b;
			if(pgcd == 0)
			{
				pgcd = b;
				break;
			}
			a = b;
			b = pgcd;
		}
		return pgcd;
	}
	
	template<typename N>
    N PPCM(N a, N b)
	{
	    return (a*b) / PGCD(a,b);
	}
}

namespace puissance
{
	template<typename N1, typename N2, typename N3>
	N1 puissance_modulaire(N1 base, N2 exposant, N3 modulo)
	{
		N1 resultat = 1;
		while (exposant > 0)
		{
			if (exposant%2)
				resultat = (base * resultat)%modulo;
			exposant /= 2;
			base = (base * base)%modulo;
		}

		return resultat;
	}

	template<typename N1, typename N2>
	N1 puissance(N1 base, N2 modulo)
	{
		N1 resultat = 1;
		while (modulo > 0)
		{
			if (modulo%2)
				resultat *= base;
			modulo /= 2;
			base *= base;
		}

		return resultat;
	}
}

namespace premiers
{
    void internal_crible(std::size_t taille, std::vector<bool> & test);
    
    template<typename N>
    void crible(std::size_t taille, std::vector<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.push_back(p);
    	}
    }
    
    template<typename N>
    void crible(std::size_t taille, std::list<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.push_back(p);
    	}
    }

    template<typename N>
    void crible(std::size_t taille, std::set<N> & premiers)
    {
    	std::vector<bool> test;
    	internal_crible(taille, test);
    	
    	for (std::size_t p = 0; p < taille + 1; ++p)
    	{
    		if (test.at(p)) premiers.insert(p);
    	}
    }    
}

namespace bezout
{
    class Bezout
    {
        int _u, _v;
        unsigned int _pgcd;
    public:
        Bezout(unsigned int a, unsigned int b);
        unsigned int pgcd() const { return _pgcd; }
        int u() const { return _u; }
        int v() const { return _v; }
    };
    
    unsigned int inverse_mod(unsigned int a, unsigned int n);
    int chinois(unsigned int a, unsigned int n, unsigned int b, unsigned int m);
}
