#include <iostream>
#include <cstdlib>
#include <gmpxx.h>

typedef mpz_class nombre;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite " << std::endl;
		return 1;
	}
	
	nombre limite(atoi(argv[1]));
	
	nombre compteur = 0;
	
	nombre l = sqrt(limite / 2 + 1) + 1;
	
	for (nombre m = 2; m < l; ++m)
	{
		// a = m^2 - n^2 ,\ \, b = 2mn ,\ \, c = m^2 + n^2 
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
					nombre ba = (b - a);
					if (abc < limite && mpz_divisible_p(c.get_mpz_t(), ba.get_mpz_t()) != 0)
					{
						
						compteur += limite / abc;
						std::cout << "(" << a << ", " << b << ", " << c << ") : " << limite / abc;
						std::cout << std::endl;
					}
				}

			}
		}
	}
	
	std::cout << "**************** SOLUTION ****************" << std::endl;
	std::cout << compteur << std::endl;
	return 0;
}
