#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <string>
#include <gmpxx.h>

typedef mpz_class nombre;

nombre power(const nombre& n, nombre b) {
    if (b == 0)
        return 1;

    nombre m(power(n, b/2));
    m *= m;

    if (b%2==1)
        m *= n;

    return m;
}

int main(int argc,char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}

	nombre limite(argv[1]);

	std::cout << "Limite : " << limite << std::endl;
	
	nombre n = 0;
	
	for (nombre i = 1; i < limite; ++i)
	{
		nombre k = power(2, i);
		k = k * (k - 1);
		
		if (k > limite)
			break;
		else
			++n;
	}
	
	nombre d = 0;
	
	for (nombre i = 2; i < limite; ++i)
	{
		nombre k = i*i - i;
		
		if (k > limite)
			break;
		else
			++d;		
	}
	
	mpq_class q("1/12345");

	mpq_class f(n);
	f = f / d;
	
	std::cout << "P(" << limite << ") = " << f << " = " << f.get_d() << std::endl;
	
	if (f < q)
	{
		std::cout << "Fuck yeah ! " << f << " < " << q << std::endl;
	}

	return 0;
}


