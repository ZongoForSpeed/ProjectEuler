#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

size_t puissance(size_t a, size_t n, size_t p)
{
	size_t resultat = 1;
	while (n > 0)
	{
		if (n%2)
			resultat = (resultat * a)%p;
			
		a = (a * a)%p;
		n /= 2;
	}
	
	return resultat;
}

int main(int, char**)
{
	vecteur count(250, 0);
	for (size_t i = 1; i <= 250250; ++i)
		count[puissance(i, i, 250)]++;
		
	for (size_t i = 250; i > 0; --i)
		std::cout << i - 1 << " ==> " << count[i-1] << std::endl;
		
	vecteur members(250, 0);
	
	nombre result = 1;
	nombre sum = 0;
	for (size_t i = 0; i < 250; ++i)
		sum += count[i];
		
	for (size_t i = 249; i > 0; --i)
	{
		result *= (count[i] + 1);
		std::cout << i << "\t~\t" << result << std::endl;
	}
	
	result *= (count[0] + 1);
	
	std::cout << "~" << result << std::endl;
	std::cout << "+" << sum << std::endl;
	
	std::cout << "Resultat = " << result + sum << std::endl;
	std::cout << "           1425480602091519" << std::endl;
}