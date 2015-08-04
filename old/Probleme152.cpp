#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <gmpxx.h>

typedef size_t nombre;
typedef mpq_class fraction;

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

class Probleme152
{
	// There are several ways to write the number 1/2 as a sum of inverse
	// squares using distinct integers.
	//
	// For instance, the numbers {2,3,4,5,7,12,15,20,28,35} can be used:
	// 
	// In fact, only using integers between 2 and 45 inclusive, there are
	// exactly three ways to do it, the remaining two being: 
	// {2,3,4,6,7,9,10,20,28,35,36,45} and {2,3,4,6,7,9,12,15,28,30,35,36,45}.
	// 
	// How many ways are there to write the number 1/2 as a sum of inverse
	// squares using distinct integers between 2 and 80 inclusive?

	nombre limite;
	
public:
	Probleme152(nombre _limite) : limite(_limite) {}
	
	void algorithme()
	{
		fraction objectif(1,2);
		std::map<fraction, nombre> resultats;
		{
			resultats[0] = 1;
			Timer t("algorithme");
			for (nombre n = 2; n < limite + 1; ++n)
			{
				fraction f(1, n*n);
				std::vector<fraction> r;
				for (std::map<fraction, nombre>::const_iterator it = resultats.begin(), en = resultats.end(); it != en; ++it)
				{
					fraction s = f + it->first;
					if (s <= objectif)
					{
						r.push_back(s);
					}
				}
				
				for (const fraction& s: r)
				{
					std::map<fraction, nombre>::iterator it = resultats.find(s);
					if (it != resultats.end())
						it->second++;
					else
						resultats[s] = 1;
				}
			}
		}
		
		std::cout << "******************** SOLUTION ********************" << std::endl;
		// for (std::map<fraction, nombre>::const_iterator it = resultats.begin(), en = resultats.end(); it != en; ++it)
		// {
		//	std::cout << it->first << " = " << it->second << std::endl;
		// }
		std::map<fraction, nombre>::iterator it = resultats.find(objectif);
		if (it != resultats.end())
			std::cout << it->second << std::endl;
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
	
	Probleme152 p(limite);
	p.algorithme();
	
	return 0;
}
