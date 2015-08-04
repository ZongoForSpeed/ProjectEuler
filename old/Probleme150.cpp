#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <gmpxx.h>
#include <limits>


typedef long long nombre;
typedef std::pair<nombre,nombre> paire;
typedef std::set<nombre> ensemble;
typedef std::vector<nombre> vecteur;
typedef std::map<nombre, vecteur> matrice;
typedef std::map<nombre, matrice> tenseur;

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

class Probleme150
{
	// In a triangular array of positive and negative integers, 
	// we wish to find a sub-triangle such that the sum of the numbers it 
	// contains is the smallest possible.
	//
	// In the example below, it can be easily verified that the marked 
	// triangle satisfies this condition having a sum of −42.
	// 
	// We wish to make such a triangular array with one thousand rows, 
	// so we generate 500500 pseudo-random numbers sk in the range ±2^19, 
	// using a type of random number generator (known as a Linear Congruential Generator) as follows:
	//
	// t := 0
	// for k = 1 up to k = 500500:
	// 		t := (615949*t + 797807) modulo 2^20
	//		sk := t−2^19
	// 
	// Thus: s1 = 273519, s2 = −153582, s3 = 450905 etc
	// 
	// Our triangular array is then formed using the pseudo-random numbers thus:
	// s1
	// s2  s3
	// s4  s5  s6 
	// s7  s8  s9  s10
	// ...
	// 
	// Sub-triangles can start at any element of the array and extend down 
	// as far as we like (taking-in the two elements directly below it from the next row,
	// the three elements directly below from the row after that, and so on).
	// The "sum of a sub-triangle" is defined as the sum of all the elements it contains.
	// Find the smallest possible sub-triangle sum.
	
	nombre limite;
	
public:
	Probleme150(nombre _limite) : limite(_limite) {}
	virtual ~Probleme150() {}
	
	static void affiche(const matrice & m)
	{
		for (matrice::const_iterator it = m.begin(), en = m.end(); it != en; ++it)
		{
			affiche(it->second);
		}
	}
	
	static void affiche(const vecteur & v)
	{
		for (vecteur::const_iterator it = v.begin(), en = v.end(); it != en; ++it)
		{
			std::cout << *it << " ";
		}
		
		std::cout << std::endl;
	}
	
	void algorithme()
	{
		matrice triangle;
		{
			Timer timer("génération triangle");
			nombre t = 0;
			nombre d20 = 1 << 20;
			nombre d19 = 1 << 19;

			for (nombre ligne = 0; ligne < limite; ++ligne)
			{
				for (nombre colonne = 0; colonne < ligne + 1; ++colonne)
				{
					t = (615949*t + 797807) % d20;
					triangle[ligne].push_back(t - d19);
				}
			}
		}
		
		nombre minimum = std::numeric_limits<nombre>::max();
		{
			Timer timer("algorithme");
			tenseur somme;
			for (nombre ligne = limite - 1; ligne >= 0; --ligne)
			{
				for (nombre colonne = 0; colonne < ligne + 1; ++colonne)
				{
					for (nombre profondeur = 0; profondeur + ligne < limite; ++profondeur)
					{
						nombre valeur = triangle[ligne][colonne];
						switch(profondeur)
						{
							case 0:	
								break;
							case 1:
								valeur += triangle[ligne+1][colonne] + triangle[ligne+1][colonne+1];
								break;
							default:
								valeur += somme[ligne+1][colonne][profondeur-1] 
										+ somme[ligne+1][colonne+1][profondeur-1] 
										- somme[ligne+2][colonne+1][profondeur-2];
								break;
						}
						
						somme[ligne][colonne].push_back(valeur);
						if (valeur < minimum)
							minimum = valeur;
					}
				}
			}
		}
		
		// affiche(triangle);
		std::cout << "Résultat : " << minimum << std::endl;
		
		// std::cout << "s1 = " << triangle[0] << std::endl;
		// std::cout << "s2 = " << triangle[1] << std::endl;
		// std::cout << "s3 = " << triangle[2] << std::endl;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << argv[0] << " limite" << std::endl;
		return 1;
	}
	
	Probleme150 p(atoi(argv[1]));
	p.algorithme();
	
	return 0;
}


