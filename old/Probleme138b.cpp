#include <iostream>
#include <cstdlib>
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

class Probleme138
{
	size_t limite;
public:
	Probleme138(size_t limite_) : limite(limite_) {}
	
	void algorithme()
	{
		nombre solution;
		{
			Timer t("algorithme");
			for (nombre n = 1; n < limite + 1; ++n)
			{
				nombre L = fibonacci(6*n + 3) / 2;
				std::cout << L << std::endl;
				solution += L;
			}
		}
		
		std::cout << "**************** SOLUTION ****************" << std::endl;
		std::cout << solution << std::endl;
	}
	
	std::pair<nombre, nombre> fibonacci_(nombre n)
	{
		if (n == 0)
			return std::make_pair(1,0);

		std::pair<nombre, nombre> p = fibonacci_(n/2);
		nombre fk = p.second;
		nombre fk_1 = p.first;
		
		if (mpz_divisible_ui_p(n.get_mpz_t(),2) != 0)
			return std::make_pair(fk * fk + fk_1 * fk_1, fk * (2 * fk_1 + fk));
		else
			return std::make_pair(fk * (2 * fk_1 + fk), (fk_1 + fk)*(fk_1 + fk) + fk * fk);
	}
	
	nombre fibonacci(nombre n)
	{
		return fibonacci_(n).second;
	}
	
private:
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite " << std::endl;
		return 1;
	}
	
	Probleme138 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}
