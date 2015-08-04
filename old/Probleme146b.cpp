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
		
	nombre sum=0,k;
	{
		Timer t("algorithme");
		for(size_t n = 10; n < limite; n += 10)
		{
			size_t reste = n%210;
			if (reste == 10 || reste == 80 || reste == 130 || reste == 200)
			{
				nombre n2 = n;
				n2 = n2 * n;
				k=( n2+1 );
				if(mpz_probab_prime_p(k.get_mpz_t(),5) )
				{
					nombre next , curr = k;
					mpz_nextprime(next.get_mpz_t(),curr.get_mpz_t());
					if( next == ( n2 + 3 ) )
					{
						curr= next ;
						mpz_nextprime(next.get_mpz_t() , curr.get_mpz_t());
						if( next == ( n2 + 7 ) )
						{
							curr = next;
							mpz_nextprime(next.get_mpz_t() , curr.get_mpz_t());
							if ( next == ( n2 + 9 ) )
							{
								curr = next;
								mpz_nextprime(next.get_mpz_t() , curr.get_mpz_t());
								if(next == ( n2 + 13 ) )
								{
									curr = next;
									mpz_nextprime(next.get_mpz_t() , curr.get_mpz_t());
									if( next == ( n2 + 27 )) 
									{
										std::cout << n << endl;
										sum += n;
									}
								}
							}
						}
					}
				}	
			}
		}  
		
	}
	
	std::cout << "******************** SOLUTION ********************" << std::endl;
	std::cout << sum << std::endl;
	
	cout<<sum<<endl;   
	return 0;
}
