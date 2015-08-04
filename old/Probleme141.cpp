#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
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

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite " << std::endl;
		return 1;
	}
	
	nombre limite(argv[1]);
	
	std::set<nombre> solutions;
	
	{
		Timer t("algorithme");
		// m^2 = v*t*(s^3*v+t);
		for (nombre t = 1; t*t*(1+t*t) < limite; ++t)
		{
			for (nombre s = t; t*(t+s*s*s) < limite; ++s) if (pgcd(s, t) == 1)
			{
				for (nombre v = 1; v*t*(v*t+s*s*s) < limite; ++v)
				{
					nombre n = v*t*(t+s*s*s*v);
					if (mpz_perfect_square_p(n.get_mpz_t()) != 0)
					{
						solutions.insert(n);
					}					
				}
			}
		}
    }    
    
    nombre solution = 0;
    for (std::set<nombre>::const_iterator it = solutions.begin(), en = solutions.end(); it != en; ++it)
    {
		solution += *it;
	}
				
	std::cout << "******************** SOLUTION ********************" << std::endl;
	std::cout << solution << std::endl;
		
	return 0;
}
