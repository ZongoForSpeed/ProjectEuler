#include <iostream>
#include <cstdlib>

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

class Probleme130
{
	// A number consisting entirely of ones is called a repunit. We shall 
	// define R(k) to be a repunit of length k; for example, R(6) = 111111.
	//
	// Given that n is a positive integer and GCD(n, 10) = 1, it can be 
	// shown that there always exists a value, k, for which R(k) is 
	// divisible by n, and let A(n) be the least such value of k; 
	// for example, A(7) = 6 and A(41) = 5.
	//
	// You are given that for all primes, p > 5, that p − 1 is divisible by 
	// A(p). For example, when p = 41, A(41) = 5, and 40 is divisible by 5.
	// 
	// However, there are rare composite values for which this is also true;
	// the first five examples being 91, 259, 451, 481, and 703.
	// 
	// Find the sum of the first twenty-five composite values of n for which
	// GCD(n, 10) = 1 and n − 1 is divisible by A(n).
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

	Probleme130( nombre _limite ) : limite(_limite)
	{
	}
	
	bool estPremier(nombre n)
	{
		for (nombre d = 2; d * d <= n; ++d)
		{
			if (n%d == 0)
				return false;
		}
		
		return true;
	}

	void algorithme()
	{
		nombre solution = 0;
		nombre compteur = 0;
		{
			nombre n = 1;
			nombre max = 0;
			Timer t("algorithme");
			while (true)
			{
				if (n%2 != 0 && n%5 != 0)
				{
					nombre k = 1;
					while (true)
					{
						if (power(10, k, 9*n) == 1)
							break;
						++k;
					}
					
					if (n%k == 1 && estPremier(n) == false)
					{
						std::cout << "A(" << n << ") = " << k << std::endl;
						solution += n;
						++compteur;
						
						if (compteur >= limite)
							break;
					}
					
				}
				
				++n;
			}

			std::cout << "***************** SOLUTION *****************" << std::endl;
			std::cout << solution << std::endl;           
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
       
	Probleme130 p(atoi(argv[1]));
	
	p.algorithme();
}


