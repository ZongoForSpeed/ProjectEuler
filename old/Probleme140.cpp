#include <iostream>
#include <cstdlib>
#include <vector>
#include <gmpxx.h>

typedef mpz_class nombre;

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


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite " << std::endl;
		return 1;
	}
	
	nombre limite = atoi(argv[1]);
	nombre somme = 0;
	nombre compteur = 0;
	
	{
		Timer t("algorithme");
		std::cout << "y² - 5x² = 44" << std::endl;
		// for (nombre n = 1; compteur < limite; ++n)
		// {
		//	nombre test = 5 * n * n + 14 * n + 1;
		//	if (mpz_perfect_square_p(test.get_mpz_t()) != 0)
		//	{
		//		somme += n;
		//		++compteur;
		//		std::cout << compteur << "\tn = " << n << "\ty = " << 5*n + 7 << "\tx = " << sqrt(((5*n + 7)*(5*n + 7)-44)/5)<< std::endl;
		//	}
		//}
		for (nombre x = 0;x < limite; ++x)
		{
			nombre y2 = 5 * x * x + 44;
			if (mpz_perfect_square_p(y2.get_mpz_t()) != 0)
			{
				std::cout << "y = " << sqrt(y2) << ", x = " << x << std::endl;
			}
		}
	}
		
	std::cout << "******************** SOLUTION ********************" << std::endl;
	std::cout << somme << std::endl;
		
	return 0;
}
