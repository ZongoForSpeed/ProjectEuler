#include <cstdlib>
#include <iostream>

#include <set>
#include <vector>

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

class Probleme146
{
	// The smallest positive integer n for which the numbers n²+1, n²+3, n²+7,
	// n²+9, n²+13, and n²+27 are consecutive primes is 10. The sum of all 
	// such integers n below one-million is 1242490.
	//
	// What is the sum of all such integers n below 150 million?

public:
	Probleme146(nombre _limite) : limite(_limite) {} 
	
	void crible(nombre taille, std::set<nombre>& premiers)
	{
		std::vector<bool> test(taille, true);
		test.at(0) = false;
		test.at(1) = false;

		for (nombre p = 2; p * p < taille; ++p)
		{
			if (test.at(p))
			{
				for (nombre k = p * p; k < taille; k += p)
				{
					test.at(k) = false;
				}
			}
		}
		
		for (nombre p = 0; p < taille; ++p)
		{
			if (test.at(p)) premiers.insert(p);
		}
	}
	
	void algorithme()
	{
		{
			Timer t("crible");
			crible(limite + 27, premiers);
		}
		
		nombre solution = 0;
		{
			Timer t("algorithme");
			for (nombre n = 10; n < limite; n += 10)
			{
				nombre reste = n%210;
				if (reste == 10 || reste == 80 || reste == 130 || reste == 200)
				{
					nombre n2 = n * n;
					if (n2%30 == 10)
					{
						{
							if (estPremier(n2 + 1) 
								&& estPremier(n2 + 3)
								&& estPremier(n2 + 7)
								&& estPremier(n2 + 9)
								&& estPremier(n2 + 13)
								&& estPremier(n2 + 27))
							{
								if (estPremier(n2 + 19) == false
									&& estPremier(n2 + 21) == false)
								{
									std::cout << n << std::endl;
									solution += n;
								}
							}
						}
					}
				}
			}
		}
		
		std::cout << "**************** SOLUTION ****************" << std::endl;
		std::cout << solution << std::endl;
	}
	
	bool estPremier(nombre n)
	{
		if (premiers.find(n) != premiers.end())
			return true;
			
		for (std::set<nombre>::const_iterator it = premiers.begin(), en = premiers.end(); it != en; ++it)
		{
			nombre p = *it;
			if (p * p > n)
				break;
				
			if (n%p == 0)
				return false;
		}
		
		return true;
	}
	
private:
	nombre limite;
	std::set<nombre> premiers;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme146 p(atoi(argv[1]));
	p.algorithme();	
	
	return 0;
}
