#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <gmpxx.h>


typedef mpz_class nombre;
typedef std::pair<nombre,nombre> paire;
typedef std::set<nombre> ensemble;
typedef std::vector<nombre> vecteur;
typedef std::map<nombre, vecteur> matrice;

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

class Probleme143
{
	// Let ABC be a triangle with all interior angles being less than 120 degrees. 
	// Let X be any point inside the triangle and let XA = p, XB = q, and XC = r.
	// 
	// Fermat challenged Torricelli to find the position of X such that p + q + r was minimised.
	// 
	// Torricelli was able to prove that if equilateral triangles AOB, BNC and AMC 
	// are constructed on each side of triangle ABC, the circumscribed circles of AOB, 
	// BNC, and AMC will intersect at a single point, T, inside the triangle. 
	// Moreover he proved that T, called the Torricelli/Fermat point, minimises p + q + r. 
	// Even more remarkable, it can be shown that when the sum is minimised, 
	// AN = BM = CO = p + q + r and that AN, BM and CO also intersect at T.
	// 
	// If the sum is minimised and a, b, c, p, q and r are all positive 
	// integers we shall call triangle ABC a Torricelli triangle. 
	// For example, a = 399, b = 455, c = 511 is an example of a Torricelli triangle, 
	// with p + q + r = 784.
	// 
	// Find the sum of all distinct values of p + q + r ≤ 120000 for Torricelli triangles.
	
	nombre limite;

public:
	Probleme143(nombre _limite) : limite(_limite) {}
	~Probleme143() {}
	
	static void intersection(const vecteur & v1, const vecteur & v2, vecteur & resultat)
	{
		resultat.clear();
		for (vecteur::const_iterator it1 = v1.begin(), en1 = v1.end(); it1 != en1; ++it1)
		{
			for (vecteur::const_iterator it2 = v2.begin(), en2 = v2.end(); it2 != en2; ++it2)
			{
				if (*it1 == *it2)
					resultat.push_back(*it1);
				else if (*it2 > *it1)
					break;
			}
		}
	}
	
	static void affiche(const vecteur & v)
	{
		for (vecteur::const_iterator it1 = v.begin(), en1 = v.end(); it1 != en1; ++it1)
		{
			std::cout << *it1 << " ";
		}
		
		std::cout << std::endl;
	}
	
	static nombre pgcd(nombre a, nombre b)
	{
		nombre c = a % b;
		while(c != 0)
		{
			a = b;
			b = c;
			c = a % b;
		}
		
		return b;
	}	
	
	void algorithme()
	{
		matrice dictionnaire;
		{   
			Timer t("recherche couple carrés");
			for (nombre m = 1; m * m < limite; ++m)
			{
				for (nombre n = 1; n < m; ++n)
				{
					if (pgcd(n, m) != 1)
						continue;
					if ((m-n)%3 == 0)
						continue;
						
					nombre a = 2*n*m + n*n;
					nombre b = m*m - n*n;
					
					if (a + b > limite)
						break;
						
					for(nombre k=1; k*(a+b) < limite; ++k)
					{ 
						nombre ak = a*k;
						nombre bk = b*k;
						
						// nombre c = sqrt(ak*ak + ak*bk + bk*bk);
						// if (c == 399 || c == 455 || c == 511)
						// std::cout << "a = " << ak << ", b = " << bk << ", c = " << c << std::endl;
												
						dictionnaire[ak].push_back(bk);
						dictionnaire[bk].push_back(ak);
					}
				}
			}
		}
		
		{
			Timer t("tri graphe");
			for (matrice::iterator it = dictionnaire.begin(), en = dictionnaire.end(); it != en; ++it)
			{
				std::sort(it->second.begin(), it->second.end());
			}
		}
		
		ensemble triplets;
		{
			Timer t("algorithme");
			for (matrice::const_iterator itM = dictionnaire.begin(), enM = dictionnaire.end(); itM != enM; ++itM)
			{
				const nombre & a = itM->first;
				const vecteur & v = itM->second;
				for (vecteur::const_iterator itV = v.begin(), enV = v.end(); itV != enV; ++itV)
				{
					const nombre & b = *itV;
					matrice::const_iterator itFind = dictionnaire.find(b);
					if (itFind != dictionnaire.end())
					{
						vecteur resultat;
						intersection(v, itFind->second, resultat);
						
						for (vecteur::const_iterator it = resultat.begin(), en = resultat.end(); it != en; ++it)
						{
							const nombre & c = *it;
							if (a + b + c <= limite)
							{
								// std::cout << "(a,b,c) = (" << a << "," << b << "," << c << ") = " << a+b+c << std::endl;
								triplets.insert(a + b + c);
							}
						}
					}
				}
			}
		}
		
		nombre solution = 0;
		for (ensemble::const_iterator it = triplets.begin(), en = triplets.end(); it != en; ++it)
		{
			solution += *it;
		}
		
		std::cout << "Nombre triplets " << triplets.size() << std::endl;
		std::cout << "Resultat " << solution << std::endl;	
	}	
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme143 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}

