#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>



typedef unsigned long long nombre;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, nombre> dictionnaire;

class Timer
{
private:
    time_t debut;
    std::string titre;

public:
    Timer(const std::string &t) : titre(t)
    {
        debut = time(NULL);
        std::cout << "Debut " << titre << " ..." << std::endl;
    }

    virtual ~Timer()
    {
        std::cout << "Fin " << titre << " en " << time(NULL) - debut << " secondes " << std::endl;
    }
};

class Probleme127
{
public:
	Probleme127(nombre taille) : m_taille(taille) {}
	
	nombre pgcd(nombre a, nombre b)
	{
		if (b == a)
			return a;
		else if (b > a)
			std::swap(a,b);
		
		nombre r = a%b;
		
		if (r == 0)
			return b;
		else 
			return pgcd(b, r);
	}

	void crible()
	{
		std::vector<bool> test(m_taille, true);
		test.at(0) = false;
		test.at(1) = false;

		for (nombre p = 2; p * p < m_taille; ++p)
		{
			if (test.at(p))
			{
				for (nombre k = p * p; k < m_taille; k += p)
				{
					test.at(k) = false;
				}
			}
		}
		
		for (nombre p = 0; p < m_taille; ++p)
		{
			if (test.at(p))
			{
				m_premiers.insert(p);
			}
		}
	}
	
	nombre rad(nombre n)
	{
		dictionnaire::const_iterator it = m_rad.find(n);
		
		if (it != m_rad.end())
			return it->second;
			
		nombre resultat = 1;
		nombre m = n;
		
		for (ensemble::const_iterator it = m_premiers.begin(), en = m_premiers.end(); it != en && n != 1; ++it)
		{
			const nombre & p = *it;
			if (n%p == 0)
			{
				resultat *= p;
				while (n%p == 0)
				{
					n /= p;
				}
			}
		}
		
		m_rad[m] = resultat;
		
		return resultat;
	}
	
	void algorithme()
	{
		{
			Timer t("crible d'Ératosthène");
			crible();
		}
		
		nombre solution = 0;
		{
			Timer t("algorithme");
			for (nombre c = 3; c < m_taille; ++c)
			{
				if (m_premiers.count(c) == 0)
				{
					nombre rad_c = rad(c);
					for (nombre b = c/2; b < c; ++b)
					{
						nombre a = c - b;
						if (a < b && pgcd(b, a) == 1 && pgcd(rad_c, b) == 1 && pgcd(rad_c, a) == 1)
						{
							nombre r = rad(a) * rad(b) * rad_c;
							if (r < c)
							{
								// std::cout << "(" << a << "," << b << "," << c << ")" << std::endl;
								// decomposition(a);
								// decomposition(b);
								// decomposition(c);
								solution += c;
							}
						}
					}
				}
			}
		}
		
		std::cout << "********* SOLUTION *********" << std::endl;
		std::cout << solution << std::endl;
	
	}
	
	void decomposition(nombre n)
	{
		std::cout << n << " = 1";
		ensemble::const_iterator it = m_premiers.begin();
		while (n != 1)
		{
			if (n%(*it) == 0)
			{
				std::cout << "*" << *it;
				n /= *it;
			}
			else
				++it;
		}
		std::cout << std::endl;
	}
	
private:
	nombre m_taille;
	ensemble m_premiers;
	dictionnaire m_rad;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " taille" << std::endl;
		return 1;
	}
	
	nombre taille = atoll(argv[1]);
	
	Probleme127 p(taille);
	p.algorithme();	
	
	return 0;
}
