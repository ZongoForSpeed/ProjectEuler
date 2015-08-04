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

class Probleme129
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

	Probleme129( nombre _limite ) : limite(_limite)
	{
	}

	void algorithme()
	{
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

					if (k > limite)
					{
						std::cout << "A(" << n << ") = " << k << std::endl;
						break;
					}
					else if (k > max)
					{
						max = k;
						std::cout << "A(" << n << ") = " << k << std::endl;
					}
				}

				++n;
			}

			std::cout << "***************** SOLUTION *****************" << std::endl;
			std::cout << n << std::endl;           
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
       
	Probleme129 p(atoi(argv[1]));
	
	p.algorithme();
}

