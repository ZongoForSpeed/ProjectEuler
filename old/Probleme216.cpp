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

using namespace std;
int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	size_t limite = atoi(argv[1]);
		
	nombre compteur = 0;
	{
		Timer t("algorithme");
		for (nombre n = 1; n < limite; ++n)
		{
			nombre t_n = 2*n*n - 1;
			if(mpz_probab_prime_p(t_n.get_mpz_t(),5))
			{
				++compteur;
			}			
		}
		
	}
	
	std::cout << "******************** SOLUTION ********************" << std::endl;
	std::cout << compteur << std::endl;
  
	return 0;
}
