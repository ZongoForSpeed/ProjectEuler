#pragma once

#include <iterator>
#include <vector>
#include <set>
#include <list>

namespace puissance
{
	template<typename Nombre1, typename Nombre2, typename Nombre3>
	Nombre1 puissance_modulaire(Nombre1 base, Nombre2 exposant, Nombre3 modulo)
	{
		Nombre1 resultat = 1;
		while (exposant > 0)
		{
			if (exposant%2)
				resultat = (base * resultat)%modulo;
			exposant /= 2;
			base = (base * base)%modulo;
		}
		return resultat;
	}

	template<typename Nombre1, typename Nombre2>
	Nombre1 puissance(Nombre1 base, Nombre2 modulo)
	{
		Nombre1 resultat = 1;
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

namespace arithmetiques
{
    template<typename Nombre>
    Nombre PGCD(Nombre a, Nombre b)
	{
		Nombre pgcd = 0;
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
	
	template<typename Nombre>
    Nombre PPCM(Nombre a, Nombre b)
	{
	    return (a*b) / PGCD(a,b);
	}
	
	template<typename Nombre, typename Iterator>
    Nombre nombre_diviseurs(Nombre n, Iterator debut, Iterator fin)
    {
        Nombre d = 1;
        for (auto it = debut; it != fin; ++it)
        {
            if (n == 1)
                break;
            const auto & p = *it;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                d *= compteur + 1;
            }
        }
        
        return d;
    }
    
    template<typename Nombre, typename Iterator>
    Nombre somme_diviseurs(Nombre n, Iterator debut, Iterator fin)
    {
        Nombre s = 1;
        for (auto it = debut; it != fin; ++it)
        {
            if (n == 1)
                break;
            const auto & p = *it;
            if (n%p == 0)
            {
                Nombre compteur = 0;
                while (n%p == 0)
                {
                    n /= p;
                    ++compteur;
                }
                s *= (puissance::puissance(p, compteur + 1) - 1)/(p - 1);
            }
        }
        
        return s;
    }
    
    template<typename Nombre>
    Nombre nombre_chiffres(Nombre n)
    {
    	Nombre d = 0;
		while (n != 0)
		{
			n /= 10;
			++d;
		}
		return d;
    }
}

namespace premiers
{
    void internal_crible(std::size_t taille, std::vector<bool> & test);
    
    template<typename Nombre, class OutputIterator>
    OutputIterator crible(std::size_t taille, OutputIterator sortie)
    {
        std::size_t taille_crible = taille / 2;
        std::vector<bool> test;
        internal_crible(taille_crible, test);
        
        *sortie = 2;
        ++sortie;
        for (std::size_t p = 1; p < taille_crible; ++p)
        {
            if (test.at(p))
            {
                *sortie = Nombre(2*p + 1);
                ++sortie;    
            }
        }
        
        return sortie;
    }
    
    template<typename Nombre>
    void crible(std::size_t taille, std::vector<Nombre> & premiers)
    {
        crible<Nombre>(taille, std::back_inserter(premiers));
    }
    
    template<typename Nombre>
    void crible(std::size_t taille, std::list<Nombre> & premiers)
    {
    	crible<Nombre>(taille, std::back_inserter(premiers));
    }

    template<typename Nombre>
    void crible(std::size_t taille, std::set<Nombre> & premiers)
    {
    	crible<Nombre>(taille, std::inserter(premiers, premiers.begin()));
    }
    
    void testCrible(std::size_t taille);
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

namespace combinatoire
{
    template<typename Nombre>
    Nombre coefficient_binomial(Nombre n, Nombre p)
    {
        if (p < 1 || n < p)
            return Nombre(1);
        if (p > n/2)
            p = n-p;
        Nombre numerateur = 1;
        Nombre denominateur = 1;
        for (Nombre k = 0; k < p; ++k)
        {
            numerateur *= (n - k);
            denominateur *= (k + 1);
        }
        
        return numerateur / denominateur;
    }
    
    template<typename Nombre>
    Nombre factoriel(Nombre n)
    {
        Nombre resultat = 1;
        for (Nombre k = 2; k <= n; ++k) resultat *= k;
        return resultat;
    }
}
