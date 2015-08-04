#include <iostream>

typedef unsigned long long nombre;

nombre puissance_modulaire(nombre p, nombre e, nombre m)
{
	nombre resultat = 1;
	p = p%m;
	while (e > 0)
	{
		if (e%2 == 1)
			resultat = (resultat * p)%m;
		e /= 2;
		p = (p * p)%m;
	}
	return resultat;
}

int main(int , char**)
{
	nombre m = 100000;
	nombre f = 64449;
	nombre f2 = 999999999987LL;
	nombre f5 = 249999999997LL;

	nombre resultat = 64449 * puissance_modulaire(2, f2 - f5, m);
	std::cout << "Resultat : " << resultat << std::endl;

	return 0;
}