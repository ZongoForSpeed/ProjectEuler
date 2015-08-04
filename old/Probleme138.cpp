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
			solution = algorithme_();
		}
		
		std::cout << "**************** SOLUTION ****************" << std::endl;
		std::cout << solution << std::endl;
	}
private:
	nombre algorithme_()
	{
		nombre somme = 0;
		nombre compteur = 0;
		
		for (nombre m = 2;;++m)
		{
			for (nombre n = 1; n < m; ++n)
			{
				nombre mn = m - n;
				if (mpz_divisible_ui_p(mn.get_mpz_t(),2) == 0)
				{
					nombre gcd;
					mpz_gcd(gcd.get_mpz_t(), n.get_mpz_t(), m.get_mpz_t());
					if (gcd == 1)
					{
						nombre a = m*m - n*n;
						nombre b = 2*m*n;
						nombre c = m*m + n*n;
						
						nombre abc = a+b+c;
						nombre base = 2 * std::min(a,b);
						nombre hauteur = std::max(a,b);
						if (base == hauteur + 1 || base == hauteur - 1)
						{
							std::cout << "(" << a << ", " << b << ", " << c << ")" << std::endl;
							somme += c;
							++compteur;
							if (compteur == limite)
								return somme;
						}
					}

				}
			}
		}
	}
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
