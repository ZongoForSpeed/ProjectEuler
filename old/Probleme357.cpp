#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

typedef size_t nombre;

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

class Probleme357
{
	// Consider the divisors of 30: 1,2,3,5,6,10,15,30.
	// It can be seen that for every divisor d of 30, d+30/d is prime.

	// Find the sum of all positive integers n not exceeding 100 000 000
	// such that for every divisor d of n, d+n/d is prime.
	
	nombre m_taille;
	std::set<nombre> m_premiers;

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
			if (test.at(p)) m_premiers.insert(p);
		}
	}
		
	bool valide(nombre n)
	{
		for (nombre d = 2; d * d < n + 1; ++d)
		{
			if (n%d == 0)
			{
				if (n%(d*d) == 0) return false;
				if (m_premiers.find(n/d + d) == m_premiers.end()) return false;
			}			
		}
		
		return true;
	}
	
public:
	Probleme357(nombre taille) : m_taille(taille) {}
	
	void algorithme()
	{
		{
			Timer t("crible");
			crible();
		}
		
		nombre solution = 0;
		{
			Timer t("algorithme");
			for (std::set<nombre>::const_iterator it = m_premiers.begin(), en = m_premiers.end(); it != en; ++it)
			{
				nombre n = *it -1;
				if (valide(n))
				{
					// std::cout << n << std::endl;
					solution += n;
				}
			}
		}
		
		std::cout << "******************** SOLUTION ********************" << std::endl;
		std::cout << solution << std::endl;
	}

};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite " << std::endl;
		return 1;
	}
	
	Probleme357 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}
