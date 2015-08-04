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

class Probleme133
{
	// A number consisting entirely of ones is called a repunit. We shall define R(k)
	// to be a repunit of length k; for example, R(6) = 111111.
	//
	// Given that n is a positive integer and GCD(n, 10) = 1, it can be shown that
	// there always exists a value, k, for which R(k) is divisible by n, and let A(n)
	// be the least such value of k; for example, A(7) = 6 and A(41) = 5.
	//
	// The least value of n for which A(n) first exceeds ten is 17.
	//
	// Find the least value of n for which A(n) first exceeds one-million.

public:
	nombre power( nombre base, nombre exposant, nombre modulo )
	{
		nombre resulat = 1;
		while (exposant > 0)
		{
			if (exposant % 2 == 1)
				resulat = (resulat * base) % modulo;
			exposant /= 2;
			base = (base * base) % modulo;
		}

		return resulat;
	}
	
	nombre A(nombre n)
	{
		nombre k = 1;
		while (true)
		{
			if (power(10, k, 9*n) == 1)
				break;
			++k;
		}
		
		return k;
	}

	Probleme133( nombre _limite ) : limite(_limite)
	{
	}

	void algorithme()
	{
		std::set<nombre> premiers;
		{
			Timer t("crible");
			crible(limite, premiers);
		}
		
		nombre solution = 0;
		{
			Timer t("algorithme");
			for (std::set<nombre>::const_iterator it = premiers.begin(), en = premiers.end(); it != en; ++it)
			{
				nombre p = *it;
				if (p == 2 || p == 5)
				{
					solution += p; es
					continue;
				}
				nombre k = A(p);
				
				// std::cout << "A(" << p << ") = " << k << std::endl;
				
				while (k%2 == 0) k /= 2;
				while (k%5 == 0) k /= 5;
				
				if (k != 1)
				{
					solution += p;
					std::cout << p << std::endl;
				}
				
			}
		}
		
		std::cout << "***************** SOLUTION *****************" << std::endl;
		std::cout << solution << std::endl;           

	}   
	
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
					test.at(k) = false;
			}
		}

		for (nombre p = 0; p < taille; ++p)
		{
			if (test.at(p))
				premiers.insert(p);
		}
	}

	
	

private:
	nombre limite;
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
       
	Probleme133 p(atoi(argv[1]));
	
	p.algorithme();
}

