#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <gmpxx.h>
#include <limits>
#include <boost/foreach.hpp>
#include <complex>

typedef long long nombre;
typedef std::complex<nombre> complexe;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, nombre> dictionnaire;
#define foreach BOOST_FOREACH

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

class Probleme153
{
	// Investigating Gaussian Integers
	// http://projecteuler.net/problem=153
	
	nombre limite;
	
public:
	Probleme153(nombre _limite) : limite(_limite) {}
	virtual ~Probleme153() {}
	
	nombre PGCD(nombre a, nombre b)
	{
		nombre pgcd = 0;
	 
		while (true)
		{
			pgcd = a % b;
			if(pgcd == 0)
			{
				pgcd = b;
				break;
			}
			a = b;
			b = pgcd;
		}
	 
		return pgcd;
	}
	
	int algorithme()
    {
		nombre resultat = 0;
		// Cas des diviseurs entiers
		{
			Timer t("Cas des diviseurs entiers");
			for (nombre i=1; i < limite + 1; i++) 
			{
				resultat += (limite/i) * i;             
			}
		}
		
		// Cas des nombres de la forme (a + ib)
		{
			Timer t("Cas des nombres complexes");
			for(nombre a = 1; a*a < limite; ++a)
			{
				for(int b=1; b < a + 1; ++b)
				{
					if(PGCD(a,b)==1)
					{  
						nombre z = (a*a+b*b);
						nombre val = (a==b)?(a+b):2*(a+b);
						for(int j=1; z*j < limite + 1; ++j)
						{
							resultat += (j*val*(limite/(z*j)));
						}
					}				
				}
			}
		}

		std::cout << "Resultat : " << resultat << std::endl;
    }
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme153 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}


